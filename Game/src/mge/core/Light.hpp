#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm.hpp"
#include "../_vs2015/LightParams.hpp"
#include "mge/core/GameObject.hpp"

/**
 * Exercise for the student: implement the Light class...
 * Imagine things like setLightType, setLightIntensity, setFalloffAngle etc, see the corresponding lectures
 */
class Light : public GameObject
{
	public:
		Light(const std::string& aName = nullptr, const glm::vec3& aPosition = glm::vec3( 2.0f, 10.0f, 5.0f ) );
		virtual ~Light();
		static Light* mapLight;

        //override set parent to register/deregister light...
		LightParams GetParams();
		void SetParams(LightParams params);
        virtual void _setWorldRecursively (World* pWorld) override;
private:
	LightParams params;
};

#endif // LIGHT_HPP
