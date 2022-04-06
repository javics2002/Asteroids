#pragma once
#include "../ecs/System.h"
#include "../utils/Vector2D.h"

const unsigned int BULLET_CD = 1000;

class FighterGunSystem : public ecs::System {
public:
	__SYSID_DECL__(ecs::_hdlr_FIGHTERGUN)

	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego no está parado y el jugador pulsa SDLK_S, enviar un mensaje
	// correspondiente con la características físicas de la bala (como en la
	// práctica 1). Recuerda que se puede disparar sólo una bala cada 0.25sec.
	void update() override;

private:
	unsigned int lastBulletTime = 0;
	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();
	// Indica si el sistema está activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no está activo)
	bool active_;
};

