/*
 * Copyright (C) 2003, 2006, 2010, 2013 Apple Inc. All rights reserved.
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

#ifndef Language_h
#define Language_h

#include <wtf/Forward.h>
#include <wtf/Vector.h>

namespace WebCore {

WEBCORE_EXPORT String defaultLanguage();
WEBCORE_EXPORT Vector<String> userPreferredLanguages();
Vector<String> userPreferredLanguagesOverride();
WEBCORE_EXPORT void overrideUserPreferredLanguages(const Vector<String>&);
size_t indexOfBestMatchingLanguageInList(const String& language, const Vector<String>& languageList, bool& exactMatch);

// The observer function will be called when system language changes.
typedef void (*LanguageChangeObserverFunction)(void* context);
WEBCORE_EXPORT void addLanguageChangeObserver(void* context, LanguageChangeObserverFunction);
WEBCORE_EXPORT void removeLanguageChangeObserver(void* context);

String displayNameForLanguageLocale(const String&);

// Called from platform specific code when the user's preferred language(s) change.
WEBCORE_EXPORT void languageDidChange();
}

#endif
