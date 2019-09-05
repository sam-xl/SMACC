namespace SS3
{
//forward declaration for initial ssr
class ssr_radial_rotate;
class ssr_radial_return;

struct ss_radial_pattern_3 : smacc::SmaccState<ss_radial_pattern_3, sm_dance_bot, ssr_radial_rotate>
{
public:
    using SmaccState::SmaccState;

    typedef mpl::list<sc::custom_reaction<smacc::EvStateFinish<ssr_radial_return>>,
                      sc::transition<EvStateFinish<ss_radial_pattern_3>, st_rotate_degrees_4>>
        reactions;

    int iteration_count;

    void onEntry()
    {
        iteration_count = 0;
    }

    sc::result react(const smacc::EvStateFinish<ssr_radial_return> &ev)
    {
        if (iteration_count++ == 4)
        {
            this->throwFinishEvent();
        }
    }
};

//forward declaration for the superstate
using SS = ss_radial_pattern_3;
#include <sm_dance_bot/superstate_routines/ssr_radial_end_point.h>
#include <sm_dance_bot/superstate_routines/ssr_radial_return.h>
#include <sm_dance_bot/superstate_routines/ssr_radial_rotate.h>
} // namespace SS3