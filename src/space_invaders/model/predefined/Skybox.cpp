#include <space_invaders/model/predefined/Skybox.hpp>
#include <space_invaders/model/HierarchicalModel.hpp>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace space_invaders::model::predefined {
    Skybox::Skybox() :
        HierarchicalModel(glm::mat4(1.0f))
    {
        walls[0].

        this->addChild(std::make_unique<HierarchicalModel>(glm::translate(glm::mat4(1.0f)), [&](const HierarchicalModel& model) {

        }));
    }
}
