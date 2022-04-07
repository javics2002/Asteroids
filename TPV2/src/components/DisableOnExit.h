#pragma once
#include "../ecs/Component.h"

struct Transform;

class DisableOnExit : public ecs::Component {
public:
	__CMPID_DECL__(ecs::_DISABLEONEXIT)

	DisableOnExit();
	virtual ~DisableOnExit();
	void initComponent() override;
	void update() override;
private:
	Transform* tr_;
};
