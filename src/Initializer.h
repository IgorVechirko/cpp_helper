#pragma once

#include <functional>
#include <mutex>
#include <map>
#include <vector>

using InitializerInitCpl = std::function<void(int)>;
using InitializerFiniCpl = std::function<void()>;

using InitializerInitFunc = std::function<void(InitializerInitCpl)>;
using InitializerFiniFunc = std::function<void(InitializerFiniCpl)>;

enum class DepName
{
	NONE,
};

class Initializer
{

private:


	enum class DepState
	{
		NONE,
		INITING,
		INIT_FAIL,
		INITED,
		FINITING,
	};

	struct Dependent
	{
		DepState m_state{DepState::NONE};
		
		InitializerInitFunc m_initFunc;
		int m_initRet{0};
		
		InitializerFiniFunc m_finiFunc;

		std::vector<DepName> m_dependents;
	};

	enum class State
	{
		NONE,
		INITING,
		INIT_SUCCESS,
		INIT_FAIL,
		FINITING,
	};

public:

	Initializer() = default;
	virtual ~Initializer() = default;

	void addDep(DepName _dep,
				InitializerInitFunc _initFunc,
				InitializerFiniFunc _finiFunc,
				const std::vector<DepName>& _deps = {});

	void startInit(InitializerInitCpl _cpl);
	void startFini(InitializerFiniCpl _cpl);

private:

	bool checkForRecursiveDep();
	std::vector<DepName> ckeckRecurse(DepName _dep, const std::vector<DepName>& _checkList);
	
	bool checkForUncompleteDep();

	void buildLevels();

	void initLevel(uint64_t _lvl);
	void finiLevel(uint64_t _lvl);

	void initCompleter(uint64_t _lvl, DepName _dep, int _ret);
	void finiCompleter(uint64_t _lvl, DepName _dep);

	void finishInit(int _ret);
	void finishFini();

private:

	std::mutex m_commonLock;

	State m_state{State::NONE};

	std::map<DepName,Dependent> m_dependents;

	std::vector<std::map<DepName,Dependent>> m_dependetsLevels;
	uint64_t m_currentLvl{0};

	InitializerInitCpl m_initCompleter;
	InitializerFiniCpl m_finiCompleter;

};