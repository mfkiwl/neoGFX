// i_animator.hpp
/*
  neogfx C++ GUI Library
  Copyright (c) 2018 Leigh Johnston.  All Rights Reserved.
  
  This program is free software: you can redistribute it and / or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <neogfx/neogfx.hpp>
#include <neolib/timer.hpp>
#include <neogfx/core/i_animator.hpp>

namespace neogfx
{
    class transition : public i_transition
    {
    public:
        transition(i_animator& aAnimator, easing aEasingFunction, double aDuration, bool aEnabled = true);
    public:
        i_animator& animator() const override;
        bool enabled() const override;
        bool disable_when_finished() const override;
        void enable(bool aDisableWhenFinished = false) override;
        void disable() override;
        easing easing_function() const override;
        double duration() const override;
        double start_time() const override;
        double mix_value() const override;
        bool finished() const override;
    public:
        void reset() override;
    public:
        transition_id cookie() const override;
    private:
        i_animator& iAnimator;
        transition_id iId;
        bool iEnabled;
        bool iDisableWhenFinished;
        easing iEasingFunction;
        double iDuration;
        mutable std::optional<double> iStartTime;
    };

    class property_transition : public transition
    {
    public:
        property_transition(i_animator& aAnimator, i_property& aProperty, easing aEasingFunction, double aDuration, bool aEnabled = true);
    public:
        void apply() override;
        bool finished() const override;
    public:
        i_property& property() const;
        const property_variant& from() const;
        const property_variant& to() const;
    public:
        bool property_destroyed() const;
    private:
        i_property& iProperty;
        neolib::destroyed_flag iPropertyDestroyed;
        neolib::sink iSink;
        property_variant iFrom;
        property_variant iTo;
        bool iUpdatingProperty;
    };

    class animator : public i_animator
    {
    public:
        animator();
    public:
        i_transition& transition(transition_id aTransitionId) override;
        transition_id add_transition(i_property& aProperty, easing aEasingFunction, double aDuration, bool aEnabled = true) override;
        void remove_transition(transition_id aTransitionId) override;
    public:
        double animation_time() const override;
    protected:
        transition_id allocate_id() override;
    private:
        void next_frame();
    private:
        neolib::callback_timer iTimer;
        neolib::cookie_jar<std::unique_ptr<i_transition>> iTransitions;
        std::chrono::time_point<std::chrono::high_resolution_clock> iZeroHour;
        double iAnimationTime;
    };
}