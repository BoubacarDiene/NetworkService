#ifndef __PLUGINS_NETWORK_LAYER_SETUP_H__
#define __PLUGINS_NETWORK_LAYER_SETUP_H__

#include <memory>
#include <string>

#include "service/plugins/ILogger.h"

namespace service::plugins::network::layer {

class Layer {

public:
    explicit Layer(const service::plugins::logger::ILogger& logger);

    ~Layer();

    Layer(const Layer&) = delete;

    Layer& operator=(const Layer&) = delete;

    Layer(Layer&&) = delete;

    Layer& operator=(Layer&&) = delete;

    void applyCommand(const std::string& pathname,
                      const std::string& value) const;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
