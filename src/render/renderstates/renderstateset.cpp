/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Copyright (C) 2021 The Qt Company Ltd and/or its subsidiary(-ies).
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
****************************************************************************/

#include "renderstateset_p.h"

#include <bitset>

#include <Qt3DRender/private/renderstates_p.h>
#include <Qt3DRender/private/qrenderstate_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {
namespace Render {

RenderStateSet::RenderStateSet()
    : m_stateMask(0)
{
}

RenderStateSet::~RenderStateSet()
{
}

template<>
void RenderStateSet::addState<StateVariant>(const StateVariant &ds)
{
    m_states.push_back(ds);
    m_stateMask |= ds.type;
}

int RenderStateSet::changeCost(RenderStateSet *previousState)
{
    if (previousState == this)
        return 0;

    int cost = 0;

    // first, find cost of any resets
    StateMaskSet invOurState = ~stateMask();
    StateMaskSet stateToReset = previousState->stateMask() & invOurState;

    std::bitset<64> bs(stateToReset);
    cost += int(bs.count());

    // now, find out how many states we're changing
    for (const StateVariant &ds : qAsConst(m_states)) {
        // if the other state contains matching, then doesn't
        // contribute to cost at all
        if (previousState->contains(ds))
            continue;

        // flat cost for now; could be replaced with a cost() method on
        // RenderState
        cost += 2;
    }

    return cost;
}

StateMaskSet RenderStateSet::stateMask() const
{
    return m_stateMask;
}

// This modifies our state to add states from others
// if we don't already contain a state with that type set
void RenderStateSet::merge(const RenderStateSet *other)
{
    const QVector<StateVariant> otherStates = other->states();

    // We only add states which are new (different type)
    for (const StateVariant &otherState : otherStates) {
        const bool canAdd = canAddStateOfType(otherState.type);
        if (canAdd)
            m_states.push_back(otherState);
    }
    m_stateMask |= other->stateMask();
}

bool RenderStateSet::canAddStateOfType(StateMask type) const
{
    return !hasStateOfType(type) || allowMultipleStatesOfType(type);
}

bool RenderStateSet::hasStateOfType(StateMask type) const
{
    return (type & stateMask());
}

bool RenderStateSet::allowMultipleStatesOfType(StateMask type) const
{
    return (type == BlendEquationArgumentsMask) ||
           (type == ClipPlaneMask);
}

bool RenderStateSet::contains(const StateVariant &ds) const
{
    // trivial reject using the state mask bits
    if (!(ds.type & stateMask()))
        return false;

    for (const StateVariant &rs : m_states) {
        if (rs == ds)
            return true;
    }
    return false;
}

} // namespace Render
} // namespace Qt3DRender

QT_END_NAMESPACE
