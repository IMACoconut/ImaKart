
template <typename T>
LoadingState<T>::LoadingState(T& load) :
	m_load(load)
{}

template <typename T>
LoadingState<T>::~LoadingState() {
	delete m_thread;
}

template <typename T>
void LoadingState<T>::Init(GameEngine* game) {
	auto& gui = game->getWindow().getGui();
	gui.removeAllWidgets();

	m_bar = tgui::LoadingBar::Ptr(gui);
    m_bar->setPosition(40, 330);
    m_bar->setSize(300, 30);
	m_bar->setMinimum(0);
	m_bar->setMaximum(100);
	m_thread = new LoadingThread<T>(m_load);
}

template <typename T>
void LoadingState<T>::Pause(GameEngine* game) {}

template <typename T>
void LoadingState<T>::Resume(GameEngine* game) {}

template <typename T>
void LoadingState<T>::Initialize(GameEngine* game) {}

template <typename T>
void LoadingState<T>::Release(GameEngine* game) {}

template <typename T>
void LoadingState<T>::Cleanup(GameEngine* game) {}

template <typename T>
void LoadingState<T>::HandleEvents(GameEngine* game) {}

template <typename T>
void LoadingState<T>::Update(GameEngine* game) {
	if(!m_bar)
		return;

	if(m_bar->getValue() >= 100) {
		std::cout << "stopping" << std::endl;
		m_thread->join();
		game->PopState();
	} else {
		m_bar->incrementValue();
	}
}

template <typename T>
void LoadingState<T>::Draw(GameEngine* game) {
	auto& window = game->getWindow();
	window.clear();
	window.display();
}
