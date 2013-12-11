#pragma once

#include <GameManager/GameState.hpp>
#include <thread>
#include <atomic>

template <typename T>
class LoadingThread {
public:
	LoadingThread(T& func) : 
		m_thread(std::bind(&LoadingThread::run, this)),
		m_running(true),
		m_func(func) 
	{}

	int getWorkDone() const {
		return 50;
	}

	void join() {
		m_running = false;
		m_thread.join();
	}

	bool isDone() {
		return !m_running;
	}

protected:
	void run() {
		m_func.load();
		m_running = false;
	}

private:
	std::thread m_thread;
	std::atomic_bool m_running;
	T& m_func;
};

template <typename T>
class LoadingState : public GameState {
public:
	LoadingState(T& load);
	~LoadingState();

	void Init(GameEngine* game);
	void Pause(GameEngine* game);
	void Resume(GameEngine* game);
	void Initialize(GameEngine* game);
	void Release(GameEngine* game);
	void Cleanup(GameEngine* game);
	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

private:
	T& m_load;
	tgui::LoadingBar::Ptr m_bar;
	LoadingThread<T>* m_thread;
};

#include <Game/States/LoadingState.inl>