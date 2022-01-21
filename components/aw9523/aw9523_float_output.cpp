#include "aw9523_float_output.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome
{
    namespace aw9523
    {

        static const char *const TAG = "aw9523_float_channel";

        void AW9523FloatOutputChannel::write_state(float state)
        {
            const float duty_rounded = roundf(state * 0xff);
            auto duty = static_cast<uint8_t>(duty_rounded);

            this->parent_->set_pin_value(this->pin_, duty);
        }

        void AW9523FloatOutputChannel::setup()
        {
            this->parent_->led_driver(this->pin_);
            this->turn_off();
        }

        void AW9523FloatOutputChannel::dump_config()
        {
            float current = (37 * this->max_power_) / 4 * (4 - this->parent_->get_divider());
            ESP_LOGCONFIG(TAG, "AW9523 PWM:");
            ESP_LOGCONFIG(TAG, "  Pin: %d", this->pin_);
            ESP_LOGCONFIG(TAG, "  Max current: %.0f ma", current);
            LOG_FLOAT_OUTPUT(this);
        }

    } // namespace aw9523
} // namespace esphome
