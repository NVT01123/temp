#pragma once
#ifndef ATHENA_SESSION_REPLAY
#define ATHENA_SESSION_REPLAY

#include "live_session.h"
#include "station.h"
#include <string>

namespace athena::replay_session {

void open(std::string input_path, SDRListener &listener,
          session::DecodeListener &decode_listener);

}; // namespace athena::replay_session

#endif
