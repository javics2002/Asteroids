// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

struct Transform;

class CollisionsSystem : public ecs::System {
public:

    CollisionsSystem();
    ~CollisionsSystem();

    __SYSID_DECL__(ecs::_hdlr_COLLISION)

    // Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
    void receive(const Message& m) override;

    // Inicializar el sistema, etc.
    void initSystem() override;

    // Si el juego está parado no hacer nada, en otro caso comprobar colisiones como
    // en la práctica 1 y enviar mensajes correspondientes.
    void update() override;

    void bulletAsteroidCollision(Transform* eTR, ecs::Entity* asteroidEntity);

    void deactivateFighter(Transform* fTR, Transform* eTR, bool& retflag);

private:
    // Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
    void onRoundOver();

    // Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
    void onRoundStart();

    // Indica si el sistema está activo o no (modificar el valor en onRoundOver y
    // onRoundStart, y en update no hacer nada si no está activo)
    bool active_;
};