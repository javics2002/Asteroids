#pragma once
#include "../ecs/System.h"

class Entity;

class AsteroidsSystem : public ecs::System {
public:
	AsteroidsSystem();
	~AsteroidsSystem();
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego está parado no hacer nada, en otro caso mover los asteroides como
	// en la práctica 1 y generar 1 asteroide nuevo cada 5 segundos (aparte
	// de los 10 al principio de cada ronda).
	void update() override;

private:
	// Para gestionar el mensaje de que ha habido un choque de un asteroide con una
	// bala. Desactivar el asteroide “a” y crear 2 asteroides como en la práctica 1,
	// y si no hay más asteroides enviar un mensaje correspondiente.
	void onCollision_AsteroidBullet(ecs::Entity* a);
	// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todos los
	// asteroides, y desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema y
	// añadir los asteroides iniciales (como en la práctica 1).
	void onRoundStart();

	void addAsteroidFrequently();
	void createAsteroids(int n);

	// El número actual de asteroides en el juego (recuerda que no puede superar un
	// límite)
	uint8_t numOfAsteroids_;
	// Indica si el sistema está activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no está activo)
	bool active_;

	uint32_t lastGenerationTime_;

	const uint32_t MAX_ASTEROIDS = 30;
	const uint32_t GENERATION_TIME = 5000;
};

