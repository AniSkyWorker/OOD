#pragma once
#include <boost\signals2.hpp>
#include "FunctionType.h"

namespace sig = boost::signals2;
using VoidSignal = sig::signal<void()>;
using VoidSlot = VoidSignal::slot_type;

using AddHarmonicSignal = sig::signal<void(FunctionType, float, float, float)>;
using AddHarmonicSlot = AddHarmonicSignal::slot_type;