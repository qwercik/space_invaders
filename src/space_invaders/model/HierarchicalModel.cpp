#include <space_invaders/model/Model.hpp>
#include <space_invaders/model/HierarchicalModel.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <list>
#include <iostream>

namespace space_invaders::model {
    HierarchicalModel::HierarchicalModel(glm::mat4&& modelMatrix, std::function<void(const HierarchicalModel&)> drawingCallback) {
        this->drawingCallback = drawingCallback;
        this->modelMatrix = std::move(modelMatrix);
    }
    
    HierarchicalModel::HierarchicalModel(HierarchicalModel&& model) {
        this->drawingCallback = std::move(model.drawingCallback);
        this->modelMatrix = std::move(model.modelMatrix);
        this->children = std::move(model.children);
        this->parent = model.parent;
        model.parent = nullptr;
    }

    HierarchicalModel& HierarchicalModel::addChild(std::unique_ptr<HierarchicalModel>&& child) {
        child->parent = this;
        this->children.push_back(std::move(child));
        return *this;
    }
    
    glm::mat4& HierarchicalModel::getModelMatrix() {
        return this->modelMatrix; 
    }

    const glm::mat4& HierarchicalModel::getModelMatrix() const {
        return this->modelMatrix; 
    }

    glm::mat4 HierarchicalModel::calculateEffectiveModelMatrix() const {
        if (this->parent) {
            return this->parent->calculateEffectiveModelMatrix() * this->modelMatrix;
        } else {
            return this->modelMatrix;
        }
    }
    
    void HierarchicalModel::draw() const {
        this->drawingCallback(*this);

        for (const auto& child : this->children) {
            child->draw();
        }
    }
}
