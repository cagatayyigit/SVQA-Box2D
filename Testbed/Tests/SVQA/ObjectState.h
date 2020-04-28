//
//  ObjectState.h
//  Testbed
//
//  Created by Tayfun Ateş on 20.10.2019.
//

#ifndef ObjectState_h
#define ObjectState_h

#include "SimulationObject.h"
#include "Box2D/Common/b2Math.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisWorld.hpp"
#include "SimulationDefines.h"

using json = nlohmann::json;

struct ObjectState
{
public:

	typedef std::shared_ptr<ObjectState> Ptr;

	ObjectState(b2VisBody* body,
        const SimulationObject::Shape& shapeType,
		const SimulationObject::Color& colorType,
        const SimulationObject::Size& sizeType) :

		body(body),
		size(sizeType),
		color(colorType),
		shape(shapeType)

	{}

	ObjectState() {
		body = nullptr;
	}

	static Ptr create(b2VisBody* body,
        const SimulationObject::Shape& shapeType,
        const SimulationObject::Color& colorType,
        const SimulationObject::Size& sizeType)
	{
		return std::make_shared<ObjectState>(body, shapeType, colorType, sizeType);
	}

	std::string getShortRepresentation()
	{
		std::string ret = "id: " + std::to_string(body->getUniqueId()) + " sh: " + SimulationObject::getRepresentation(shape) + " sz: " + SimulationObject::getRepresentation(size) + " col: " + SimulationObject::getRepresentation(color);
		return ret;
	}

	std::string getImagePath()
	{
		std::string shStr = SimulationObject::getRepresentation(shape);
		std::string colStr = SimulationObject::getRepresentation(color);
        std::string szStr = SimulationObject::getRepresentation(size);

		//std::string basePath = "\"..\\Testbed\\Data\\Images\\";
        std::string basePath = "\"../Testbed/Data/Images/";

		std::string result = basePath + shStr + "_" + szStr + "_" + colStr  + ".png";

		//return "\"C:\\Users\\Cagatay\\Projects\\SVQA\\SVQA-Box2D\\Testbed\\Data\\Images\\" + type + "_" + color + ".png";
		return result;
	}

	void to_json(json& j) const {
		if (body) {
            
            auto pos = body->GetPosition();
			j.emplace("active", body->IsActive());
            j.emplace("2dCoords", std::vector<float>({pos.x, pos.y}));
			j.emplace("angle", body->GetAngle());
            auto linearVelocity = body->GetLinearVelocity();
			j.emplace("2dLinearVelocity", std::vector<float>({linearVelocity.x, linearVelocity.y}));
			j.emplace("angularVelocity", body->GetAngularVelocity());
			j.emplace("linearDamping", body->GetLinearDamping());
			j.emplace("angularDamping", body->GetAngularDamping());
			j.emplace("bodyType", body->GetType());
			j.emplace("uniqueID", body->getUniqueId());

			j.emplace("gravityScale", body->GetGravityScale());
			j.emplace("bullet", body->IsBullet());
			j.emplace("allowSleep", body->IsSleepingAllowed());
			j.emplace("awake", body->IsAwake());
			j.emplace("fixedRotation", body->IsFixedRotation());

			b2MassData massData;
			body->GetMassData(&massData);

			j.emplace("massData-mass", massData.mass);
			j.emplace("massData-centerX", massData.center.x);
			j.emplace("massData-centerY", massData.center.y);
			j.emplace("massData-I", massData.I);
		}
        
        j.emplace("friction", body->GetFixtureList()->GetFriction());
        j.emplace("restitution", body->GetFixtureList()->GetRestitution());
        j.emplace("density", body->GetFixtureList()->GetDensity());
        
		j.emplace("color", color);
		j.emplace("shape", shape);
        j.emplace("size", size);
	}

	void from_json(const json& j, WORLD* toWorld) {
		bool active, bullet, allowSleep, awake, fixedRotation;
		float angle, angVel, linearDamp, angDamp;
		float gravityScale, friction, restitution, density;
		int bodyType, uniqueID;

		j.at("active").get_to(active);
        
        std::vector<float> pos;
		j.at("2dCoords").get_to(pos);
		j.at("angle").get_to(angle);
        std::vector<float> linearVelocity;
		j.at("2dLinearVelocity").get_to(linearVelocity);
		j.at("angularVelocity").get_to(angVel);
		j.at("linearDamping").get_to(linearDamp);
		j.at("angularDamping").get_to(angDamp);
		j.at("bodyType").get_to(bodyType);
        j.at("uniqueID").get_to(uniqueID),
		j.at("friction").get_to(friction);
        j.at("restitution").get_to(restitution);
        j.at("density").get_to(density);
		j.at("color").get_to(color);
		j.at("shape").get_to(shape);
        j.at("size").get_to(size);

		j.at("gravityScale").get_to(gravityScale);
		j.at("bullet").get_to(bullet);
		j.at("allowSleep").get_to(allowSleep);
		j.at("awake").get_to(awake);
		j.at("fixedRotation").get_to(fixedRotation);

		b2MassData massData;
		j.at("massData-mass").get_to(massData.mass);
		j.at("massData-centerX").get_to(massData.center.x);
		j.at("massData-centerY").get_to(massData.center.y);
		j.at("massData-I").get_to(massData.I);
        
        auto simObject = SimulationObject(shape, color, size);
		ShapePtr shapePtr = simObject.getShape();

		b2BodyDef bd;
		bd.type = (b2BodyType)bodyType;
		bd.position = b2Vec2(pos[0], pos[1]);
		bd.angle = angle;
		bd.linearVelocity = b2Vec2(linearVelocity[0], linearVelocity[1]);
		bd.angularVelocity = angVel;
		bd.linearDamping = linearDamp;
		bd.angularDamping = angDamp;

		bd.allowSleep = allowSleep;
		bd.awake = awake;
		bd.bullet = bullet;
		bd.fixedRotation = fixedRotation;

		body = (BODY*)toWorld->CreateBody(&bd);

		b2FixtureDef fd = b2FixtureDef();
		fd.friction = friction;
        fd.restitution = restitution;
        fd.density = density;
		fd.shape = shapePtr.get();

		body->CreateFixture(&fd);
		body->SetActive(active);
		body->SetMassData(&massData);
		body->SetGravityScale(gravityScale);
        body->setUniqueId(uniqueID);

#if !USE_DEBUG_DRAW
		body->setColor(simObject.getColor());
#endif

		body->SetUserData(this);
	}

	BODY* body;
	SimulationObject::Color color;
	SimulationObject::Shape shape;
    SimulationObject::Size size;
};



#endif /* ObjectState_h */
