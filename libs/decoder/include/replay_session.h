#pragma once
#ifndef ATHENA_SESSION_REPLAY
#define ATHENA_SESSION_REPLAY

#include "station.h"
#include <string>

namespace athena::replay_session {

void open(std::string input_path, SDRListener &listener);

}; // namespace athena::replay_session

#endif
