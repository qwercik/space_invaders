#pragma once

#include <string>
#include <space_invaders/model/BasicModel.hpp>

namespace space_invaders::model {
    class ModelFromFile : public BasicModel {
    public:
        ModelFromFile(const std::string& filename);
        bool isOk() const;

    private:
        bool ok = false;
    };
}
