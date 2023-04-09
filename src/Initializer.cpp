#include "Initializer.h"

#include <set>
#include <string>
#include <iterator>

void Initializer::addDep(DepName _dep,
							InitializerInitFunc _initFunc,
							InitializerFiniFunc _finiFunc,
							const std::vector<DepName> &_deps)
{
	m_dependents[_dep] = Dependent{DepState::NONE,
								   _initFunc,
								   0,
								   _finiFunc,
								   _deps};
}
void Initializer::buildLevels()
{
	std::set<DepName> baseDeps;

	while (!m_dependents.empty())
	{
		std::map<DepName, Dependent> lvl;

		for (auto depIt = m_dependents.begin(); depIt != m_dependents.end();)
		{
			bool allDeps = true;
			for (auto depName : depIt->second.m_dependents)
			{
				allDeps &= (baseDeps.find(depName) != baseDeps.end());

				if (!allDeps)
					break;
			}

			if (allDeps)
			{
				lvl.insert(std::move(*depIt));

				depIt = m_dependents.erase(depIt);
			}
			else
			{
				++depIt;
			}
		}

		for (const auto &depPair : lvl)
		{
			baseDeps.insert(depPair.first);
		}
		m_dependetsLevels.push_back(std::move(lvl));
	}

	/*for(uint32_t lvl = 0; lvl < m_dependetsLevels.size(); ++lvl)
	{
		std::string lvlDeps;
		for(const auto& depPair : m_dependetsLevels[lvl])
		{
			lvlDeps += std::to_string(static_cast<uint8_t>(depPair.first)) += " ";
		}
		SW_ERR_LOG("Deps on %d lvl: %s", lvl, lvlDeps.c_str());
	}*/
}
bool Initializer::checkForRecursiveDep()
{
	for (const auto &depPair : m_dependents)
	{
		const auto &recurseRound = ckeckRecurse(depPair.first, depPair.second.m_dependents);

		if (!recurseRound.empty())
		{
			std::string round = std::to_string(static_cast<uint8_t>(depPair.first)) += " ";
			for (auto dependent : recurseRound)
			{
				round += std::to_string(static_cast<uint8_t>(dependent)) += " ";
			}

			printf("Recursive dependets detected:\n %s", round.c_str());
			return true;
		}
	}

	return false;
}
std::vector<DepName> Initializer::ckeckRecurse(DepName _dep, const std::vector<DepName> &_checkList)
{
	std::vector<DepName> ret;

	for (const auto &checkingDep : _checkList)
	{
		if (_dep == checkingDep)
		{
			ret.push_back(checkingDep);
			return ret;
		}

		auto findIt = m_dependents.find(checkingDep);
		if (findIt != m_dependents.end())
		{
			const auto &recurse = ckeckRecurse(_dep, findIt->second.m_dependents);

			if (!recurse.empty())
			{
				ret.push_back(checkingDep);
				std::copy(recurse.begin(), recurse.end(), std::inserter(ret, ret.end()));
				return ret;
			}
		}
	}

	return ret;
}
bool Initializer::checkForUncompleteDep()
{
	for (const auto &depPair : m_dependents)
	{
		for (auto checkingPed : depPair.second.m_dependents)
		{
			if (m_dependents.find(checkingPed) == m_dependents.end())
			{
				printf("No implementation for dependent %d", static_cast<uint8_t>(checkingPed));
				return true;
			}
		}
	}

	return false;
}
void Initializer::startInit(InitializerInitCpl _cpl)
{
	std::unique_lock lock(m_commonLock);

	if (m_state != State::NONE)
	{
		printf("Invalid state %d", static_cast<uint8_t>(m_state));
		_cpl(-1);
		return;
	}

	if (checkForRecursiveDep() || checkForUncompleteDep())
	{
		printf("Invalid initializer");

		lock.unlock();
		_cpl(-1);
		return;
	}

	m_state = State::INITING;
	m_initCompleter = _cpl;

	buildLevels();
	lock.unlock();

	initLevel(0);
}
void Initializer::initLevel(uint64_t _lvl)
{
	std::unique_lock lock(m_commonLock);

	if (_lvl < m_dependetsLevels.size())
	{
		m_currentLvl = _lvl;

		std::vector<std::pair<DepName, InitializerInitFunc>> initersToRun;

		for (auto &depPair : m_dependetsLevels[m_currentLvl])
		{
			if (!depPair.second.m_initFunc)
			{
				depPair.second.m_state = DepState::INITED;
			}
			else
			{
				depPair.second.m_state = DepState::INITING;
				initersToRun.push_back(std::pair<DepName, InitializerInitFunc>(depPair.first, depPair.second.m_initFunc));
			}
		}

		// In case of completing initers in the same thread
		// run they in function local context which doesn't afected
		// even if object will be changed or destroyed
		// in the same thread in some init function
		lock.unlock();
		if (!initersToRun.empty())
		{
			for (auto &initerPair : initersToRun)
			{
				initerPair.second(
					std::bind(&Initializer::initCompleter,
								this,
								m_currentLvl,
								initerPair.first,
								std::placeholders::_1));
			}
		}
		else
		{
			initCompleter(m_currentLvl, DepName::NONE, 0);
		}
	}
}
void Initializer::initCompleter(uint64_t _lvl, DepName _dep, int _ret)
{
	std::unique_lock lock(m_commonLock);

	if (_lvl < m_dependetsLevels.size())
	{
		auto &depsLvl = m_dependetsLevels[_lvl];

		auto depIt = depsLvl.find(_dep);
		if (depIt != depsLvl.end())
		{
			depIt->second.m_state = _ret == 0 ? DepState::INITED : DepState::INIT_FAIL;
			depIt->second.m_initRet = _ret;
		}

		bool allDepsOnLvlComplete = true;
		bool allDepsOnLvlSuccess = true;
		int lastErr = 0;

		for (const auto &depPair : depsLvl)
		{
			allDepsOnLvlComplete &= (depPair.second.m_state == DepState::INIT_FAIL ||
										depPair.second.m_state == DepState::INITED);
			allDepsOnLvlSuccess &= (depPair.second.m_state == DepState::INITED);
			lastErr = (depPair.second.m_state == DepState::INIT_FAIL ? depPair.second.m_initRet : lastErr);

			if (!allDepsOnLvlComplete)
				break;
		}

		if (allDepsOnLvlComplete)
		{
			//printf("Init lvl complete %d", m_currentLvl);

			if (allDepsOnLvlSuccess)
			{
				auto lastLvl = (m_currentLvl + 1 == m_dependetsLevels.size());
				if (lastLvl)
				{
					m_state = State::INIT_SUCCESS;

					lock.unlock();
					finishInit(0);
					lock.lock();
				}
				else
				{
					lock.unlock();
					initLevel(m_currentLvl + 1);
					lock.lock();
				}
			}
			else
			{
				m_state = State::INIT_FAIL;

				lock.unlock();
				finishInit(lastErr);
				lock.lock();
			}
		}
	}
}
void Initializer::finishInit(int _ret)
{
	std::unique_lock lock(m_commonLock);

	auto cpl = m_initCompleter;
	m_initCompleter = nullptr;

	lock.unlock();
	cpl(_ret);
}
void Initializer::startFini(InitializerFiniCpl _cpl)
{
	std::unique_lock lock(m_commonLock);

	if (m_state != State::INIT_SUCCESS && m_state != State::INIT_FAIL)
	{
		printf("Invalid state %d", static_cast<uint8_t>(m_state));

		lock.unlock();
		_cpl();
		return;
	}

	m_state = State::FINITING;
	m_finiCompleter = _cpl;

	lock.unlock();
	finiLevel(m_currentLvl);
}
void Initializer::finiLevel(uint64_t _lvl)
{
	std::unique_lock lock(m_commonLock);

	if (_lvl < m_dependetsLevels.size())
	{
		m_currentLvl = _lvl;

		std::vector<std::pair<DepName, InitializerFiniFunc>> finitersToRun;

		for (auto &depPair : m_dependetsLevels[m_currentLvl])
		{
			if (!depPair.second.m_finiFunc)
			{
				depPair.second.m_state = DepState::NONE;
			}
			else if (depPair.second.m_state == DepState::INIT_FAIL)
			{
				depPair.second.m_state = DepState::NONE;
			}
			else
			{
				depPair.second.m_state = DepState::FINITING;
				finitersToRun.push_back(std::pair<DepName, InitializerFiniFunc>(depPair.first, depPair.second.m_finiFunc));
			}
		}

		lock.unlock();
		if (!finitersToRun.empty())
		{
			for (auto &finiterPair : finitersToRun)
			{
				finiterPair.second(
					std::bind(&Initializer::finiCompleter,
								this,
								m_currentLvl,
								finiterPair.first));
			}
		}
		else
		{
			finiCompleter(m_currentLvl, DepName::NONE);
		}
	}
}
void Initializer::finiCompleter(uint64_t _lvl, DepName _dep)
{
	std::unique_lock lock(m_commonLock);

	if (_lvl < m_dependetsLevels.size())
	{
		auto &depsLvl = m_dependetsLevels[_lvl];

		auto depIt = depsLvl.find(_dep);
		if (depIt != depsLvl.end())
		{
			depIt->second.m_state = DepState::NONE;
		}

		bool allDepsOnLvlComplete = true;

		for (const auto &depPair : depsLvl)
		{
			allDepsOnLvlComplete &= (depPair.second.m_state == DepState::NONE);

			if (!allDepsOnLvlComplete)
				break;
		}

		if (allDepsOnLvlComplete)
		{
			//printf("Fini lvl complete %d", m_currentLvl);

			auto lastLvl = (m_currentLvl == 0);
			if (lastLvl)
			{
				m_state = State::NONE;

				lock.unlock();
				finishFini();
				lock.lock();
			}
			else
			{
				lock.unlock();
				finiLevel(m_currentLvl - 1);
				lock.lock();
			}
		}
	}
}
void Initializer::finishFini()
{
	std::unique_lock lock(m_commonLock);

	auto cpl = m_finiCompleter;
	m_finiCompleter = nullptr;

	lock.unlock();
	cpl();
}