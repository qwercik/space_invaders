#pragma once

#include <space_invaders/model/Model.hpp>
#include <glm/glm.hpp>
#include <functional>
#include <memory>
#include <list>

namespace space_invaders::model {
    class HierarchicalModel : public Model {
    public:
        HierarchicalModel(glm::mat4&& modelMatrix, std::function<void(const HierarchicalModel&)> drawingCallback);
        HierarchicalModel(HierarchicalModel&& model);


        HierarchicalModel& addChild(std::unique_ptr<HierarchicalModel>&& child);
        glm::mat4& getModelMatrix();
        const glm::mat4& getModelMatrix() const;
        glm::mat4 calculateEffectiveModelMatrix() const;

        virtual void draw() const override;

    private:
        std::function<void(const HierarchicalModel&)> drawingCallback;

        glm::mat4 modelMatrix;
        std::list<std::unique_ptr<HierarchicalModel>> children;
        HierarchicalModel *parent = nullptr;
    };
}
