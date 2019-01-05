#pragma once

#include "base.hh"

namespace fiio::config{
    class jpeg : public base{
        public:
            jpeg();
            jpeg(std::string fname);

            void load(std::string fname) override;
            void save(std::string fname) override;

            inline int quality() { return _quality; }
            void set_quality(int value);

        private:
            int _quality;
    };
}
