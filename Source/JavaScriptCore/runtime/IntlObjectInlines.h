/*
 * Copyright (C) 2016 Yusuke Suzuki <yusuke.suzuki@sslab.ics.keio.ac.jp>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(INTL)

#include "IntlObject.h"
#include "JSObject.h"

namespace JSC {

template<typename IntlInstance, typename Constructor, typename Factory>
JSValue constructIntlInstanceWithWorkaroundForLegacyIntlConstructor(ExecState& state, JSValue thisValue, Constructor* callee, Factory factory)
{
    // FIXME: Workaround to provide compatibility with ECMA-402 1.0 call/apply patterns.
    // https://bugs.webkit.org/show_bug.cgi?id=153679
    VM& vm = state.vm();
    if (!jsDynamicCast<IntlInstance*>(thisValue)) {
        JSValue prototype = callee->getDirect(vm, vm.propertyNames->prototype);
        if (JSObject::defaultHasInstance(&state, thisValue, prototype)) {
            JSObject* thisObject = thisValue.toObject(&state);
            if (state.hadException())
                return jsUndefined();

            IntlInstance* instance = factory(vm);
            if (state.hadException())
                return jsUndefined();

            thisObject->putDirect(vm, vm.propertyNames->intlSubstituteValuePrivateName, instance);
            return thisObject;
        }
    }

    return factory(vm);
}

} // namespace JSC

#endif // ENABLE(INTL)
