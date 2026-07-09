// ==WindhawkMod==
// @id              library-pane
// @name            Library Pane (Public Beta 3)
// @description     Restores the library information pane that shows atop library folders in Windows 7.
// @name:es         Panel de Biblioteca
// @description:es  Restaura el panel de información de la biblioteca que aparecía en la parte superior de las carpetas de biblioteca en Windows 7.
// @name:pt         Painel da Biblioteca
// @description:pt  Restaura o painel de informações da biblioteca que aparecia no topo das pastas de biblioteca no Windows 7.
// @name:ja         ライブラリ ペイン
// @description:ja  Windows 7 のライブラリ フォルダー上部に表示されていた、ライブラリ情報ペインを復元します。
// @name:ru         Область библиотек
// @description:ru  Восстанавливает область информации о библиотеках, которая отображается над папками библиотек в Windows 7.
// @name:uk         Область бібліотек
// @description:uk  Відновлює область інформації про бібліотеки, яка відображається над папками бібліотек Windows 7.
// @name:tr         Kitaplık Bölmesi
// @description:tr  Windows 7’de kitaplık klasörlerinin üst bölümünde gösterilen kitaplık bilgi panelini geri getirir.
// @version         1.0
// @author          Leymonaide
// @github          https://github.com/Leymonaide
// @twitter         https://twitter.com/Leym0naide
// @homepage        https://leymonaide.github.io/
// @include         explorer.exe
// @compilerOptions -lcomctl32 -luuid -lole32 -lshlwapi -loleaut32 -lntdll -O0
// ==/WindhawkMod==

// HI! -O0 is set for fast compilation during development. That flag should be
// removed for release.

// BUGBUG(#3): There is a super rare crash that I managed to cause when
// navigating to a library subfolder. I messed with the grouping of the parent
// folder (a top level library folder) beforehand.
// 2025-12-16: Does this still occur?

// Translations:
struct Translations
{
    LANGID langId;
    LPCWSTR homeTitle;
    LPCWSTR homeDescription;
    LPCWSTR folderTitle;
    LPCWSTR folderIncludesLabel;
    LPCWSTR locationSingular;
    LPCWSTR locationPlural;
    LPCWSTR arrangeBy;
    LPCWSTR homegroupTitle;
    LPCWSTR homegroupRootDescription;
    LPCWSTR homegroupLibrariesDescription;
};

constexpr Translations kStrings[] = {
    {
        .langId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
        .homeTitle = L"Libraries",
        .homeDescription = L"Open a library to see your files "
                           L"and arrange them by folder, "
                           L"date, and other properties.",
        .folderTitle = L"%s library",
        .folderIncludesLabel = L"Includes: ",
        .locationSingular = L"1 location",
        .locationPlural = L"%d locations",
        .arrangeBy = L"Arrange by:",
        .homegroupTitle = L"HomeGroup",
        .homegroupRootDescription = L"Open a library to see homegroup files "
                                    L"and arrange them by folder, date, and "
                                    L"other properties.",
        .homegroupLibrariesDescription = L"Browse available libraries shared "
                                         L"by other members of your homegroup.",
    },
    // es-ES TODO: Still needs Homegroup strings.
    {
        .langId = MAKELANGID(LANG_SPANISH, SUBLANG_DEFAULT),
        .homeTitle = L"Bibliotecas",
        .homeDescription = L"Abra una biblioteca para ver sus archivos y "
                           L"organícelos por carpeta, fecha y otras "
                           L"propiedades.",
        .folderTitle = L"Biblioteca %s",
        .folderIncludesLabel = L"Incluye: ",
        .locationSingular = L"Ubicación de 1",
        .locationPlural = L"%d ubicaciones",
        .arrangeBy = L"Organizar por:",
    },
    // pt-BR TODO: Still needs Homegroup strings.
    {
        .langId = MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE_BRAZILIAN),
        .homeTitle = L"Bibliotecas",
        .homeDescription = L"Abra uma biblioteca para visualizar os arquivos e "
                           L"organizá-los por pasta, data e outras "
                           L"propriedades.",
        .folderTitle = L"Biblioteca %s",
        .folderIncludesLabel = L"Inclui: ",
        .locationSingular = L"1 local",
        .locationPlural = L"%d locais",
        .arrangeBy = L"Organizar por:",
    },
    // ja-JP TODO: Still needs Homegroup strings.
    {
        .langId = MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN),
        .homeTitle = L"ライブラリ",
        .homeDescription = L"ライブラリを開いてファイルを表示し、"
                           L"フォルダー別、日付別、またはその他の基準に従って"
                           L"整列します。",
        .folderTitle = L"%s ライブラリ",
        .folderIncludesLabel = L"対象フォルダー: ",
        .locationSingular = L"1 か所",
        .locationPlural = L"%d か所",
        .arrangeBy = L"並べ替え:",
    },
    // Provided thanks to krisskross1225 on Discord
    // pl-PL TODO: Still needs Homegroup strings.
    {
        .langId = MAKELANGID(LANG_POLISH, SUBLANG_POLISH_POLAND),
        .homeTitle = L"Biblioteki",
        .homeDescription = L"Otwórz bibliotekę, aby zobaczyć swoje pliki i "
                           L"uporządkować je według folderu, daty oraz innych "
                           L"właściwości.",
        .folderTitle = L"Biblioteka %s",
        .folderIncludesLabel = L"Zawiera: ",
        .locationSingular = L"1 lokalizację",
        .locationPlural = L"Lokalizacji — %d",
        .arrangeBy = L"Rozmieść według:",
    },
    // Provided thanks to Brawllux
    {
        .langId = MAKELANGID(LANG_TURKISH, SUBLANG_TURKISH_TURKEY),
        .homeTitle = L"Kitaplıklar",
        .homeDescription = L"Dosyalarınızı görmek için bir kitaplık "
                           L"açın ve klasör, tarih ve diğer özellikleri "
                           L" kullanarak dosyalarınızı düzenleyin.",
        .folderTitle = L"%s kitaplığı",
        .folderIncludesLabel = L"İçindekiler: ",
        .locationSingular = L"1 konum",
        .locationPlural = L"%d konum",
        .arrangeBy = L"Düzenleme ölçütü:",
        .homegroupTitle = L"Ev Grubu",
        .homegroupRootDescription = L"Ev grubu dosyalarını görmek ve klasör, "
                                    L"tarih ve diğer özelliklere göre düzenlemek "
                                    L"için bir kitaplık açın.",
        .homegroupLibrariesDescription = L"Ev grubunuzun diğer üyeleri tarafından paylaşılan, "
                                         L"kullanılabilir kitaplıklara göz atın."
    },
    // Provided thanks to ThatFedoraDude
    {
        .langId = MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT),
        .homeTitle = L"Библиотеки",
        .homeDescription = L"Откройте библиотеку, чтобы просмотреть файлы и "
                           L"отсортировать их по папке, "
                           L"дате и другим свойствам.",
        .folderTitle = L"Библиотека \"%s\"",
        .folderIncludesLabel = L"Включает: ",
        .locationSingular = L"1 место",
        .locationPlural = L"%d места",
        .arrangeBy = L"Упорядочить:",
        .homegroupTitle = L"Домашняя группа",
        .homegroupRootDescription = L"Откройте библиотеку, чтобы просмотреть файлы домашней группы и "
                                    L"отсортировать их по папке, "
                                    L"дате и другим свойствам.",
        .homegroupLibrariesDescription = L"Просмотрите доступные библиотеки, которыми "
                                         L"пользуются другие участники вашей домашней группы.",
    },
    // Provided thanks to ThatFedoraDude
    {
        .langId = MAKELANGID(LANG_UKRAINIAN, SUBLANG_DEFAULT),
        .homeTitle = L"Бібліотеки",
        .homeDescription = L"Відкрийте бібліотеку, щоб переглянути файли та "
                           L"відсортувати їх за папкою, "
                           L"датою та іншими властивостями.",
        .folderTitle = L"Бібліотека \"%s\"",
        .folderIncludesLabel = L"Включає: ",
        .locationSingular = L"1 місце",
        .locationPlural = L"%d місця",
        .arrangeBy = L"Впорядкувати:",
        .homegroupTitle = L"Домашня група",
        .homegroupRootDescription = L"Відкрийте бібліотеку, щоб переглянути файли домашньої групи та "
                                    L"відсортувати їх за папкою, "
                                    L"датою та іншими властивостями.",
        .homegroupLibrariesDescription = L"Перегляньте доступні бібліотеки, якими "
                                         L"користуються інші учасники вашої домашньої групи.",
    },
    // Provided thanks to ImSwordQueen
    // it-IT TODO: Still needs Homegroup strings.
    {
        .langId = MAKELANGID(LANG_ITALIAN, SUBLANG_ITALIAN),
        .homeTitle = L"Raccolte",
        .homeDescription = L"Aprire una raccolta per visualizzare i file "
                           L" e ordinarli in base a cartella, "
                           L"data e altre propriet\xE0.",
        .folderTitle = L"Raccolta %s",
        .folderIncludesLabel = L"Include: ",
        .locationSingular = L"1 percorso",
        .locationPlural = L"%d percorsi",
        .arrangeBy = L"Disponi per:",
    },
};

constexpr int kTranslationsEnUsIndex = 0;
static_assert(kStrings[kTranslationsEnUsIndex].langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));

//======================================================================================================================

// ==WindhawkModReadme==
/*
# Restore Library Pane

This mod restores the library information pane seen atop a library folder's view in Windows Explorer in Windows 7.

This is a public beta release to my friends on Discord for early feedback. Please let
me (loveofleytoo/Leymonaide) know about any problems you encounter. If the mod crashes for you, then please provide details on how
to reproduce the crash if possible.

## Compatibility

The mod has been tested on Windows 8, 8.1, 10, and 11 through [TODO: Specify upper bounds version].

This mod works both with and without Aerexplorer. However, if you are using Revert8Plus, then this mod will conflict with
their Aerexplorer fork's own restore library pane feature, which does not work as well as this mod. In such cases, please
disable the respective setting for that mod or replace it with the official Aerexplorer.

## Credits

The original project was written by OjasK.

DirectUI headers copied from [the headers wonderfully provided by the World Windows Federation](https://github.com/world-windows-federation/dui70).
I am very thankful for their work.

[Isabella Lulamoon](//github.com/kawapure) contributed 32-bit/WOW64 support and helped ensure Windows 8, 8.1, and 11
support.

[AllieTheFox](//github.com/AllieTheFox) helped me with DirectUI a bit, which helped the development of this mod.

All of the members of the [World Windows Federation]() and [ExplorerEx]() Discord servers for helping test the mod!

### Translations

- Polish translation provided by `krisskross1225` from the explorer7 Discord server.
- Turkish translation provided by Brawllux from the WinClassic community and explorer7 Discord server.
- Russian and Ukrainian translations provided by ThatFedoraDude.
- Italian translation provided by ImSwordQueen.

If you want to provide a translation for yourself, please open a pull request
or contact me on Discord, where my username is `loveofleytoo`.
*/
// ==/WindhawkModReadme==

#include <exdisp.h>
#include <minwindef.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <shobjidl.h>
#include <strsafe.h>
#include <windef.h>
#include <windhawk_api.h>
#include <windhawk_utils.h>
#include <windows.h>
#include <winerror.h>
#include <winnt.h>
#include <winscard.h>
#include <cwchar>
#include <intsafe.h>
#include <oleacc.h> // IAccessible, used by DUI70.
#include <XmlLite.h> // IXmlReader, used by DUI70.
#include <vector>
#include <wrl.h>
#include <wil/result.h>

#define RUNTIME_ASSERT(x, msg) (([&]() { auto __temp = x; if (!(__temp)) Wh_Log(L"ASSERTION FAIL %d %s", __LINE__, L## #msg); return __temp; })())

/* Debugging assertions and traps
 * Portable Snippets - https://github.com/nemequ/portable-snippets
 * Created by Evan Nemerson <evan@nemerson.com>
 *
 *   To the extent possible under law, the authors have waived all
 *   copyright and related or neighboring rights to this code.  For
 *   details, see the Creative Commons Zero 1.0 Universal license at
 *   https://creativecommons.org/publicdomain/zero/1.0/
 */

#if !defined(PSNIP_DEBUG_TRAP_H)
#define PSNIP_DEBUG_TRAP_H

#if !defined(PSNIP_NDEBUG) && defined(NDEBUG) && !defined(PSNIP_DEBUG)
#  define PSNIP_NDEBUG 1
#endif

#if defined(__has_builtin) && !defined(__ibmxl__)
#  if __has_builtin(__builtin_debugtrap)
#    define psnip_trap() __builtin_debugtrap()
#  elif __has_builtin(__debugbreak)
#    define psnip_trap() __debugbreak()
#  endif
#endif
#if !defined(psnip_trap)
#  if defined(_MSC_VER) || defined(__INTEL_COMPILER)
#    define psnip_trap() __debugbreak()
#  elif defined(__ARMCC_VERSION)
#    define psnip_trap() __breakpoint(42)
#  elif defined(__ibmxl__) || defined(__xlC__)
#    include <builtins.h>
#    define psnip_trap() __trap(42)
#  elif defined(__DMC__) && defined(_M_IX86)
     static inline void psnip_trap(void) { __asm int 3h; }
#  elif defined(__i386__) || defined(__x86_64__)
     static inline void psnip_trap(void) { __asm__ __volatile__("int3"); }
#  elif defined(__thumb__)
     static inline void psnip_trap(void) { __asm__ __volatile__(".inst 0xde01"); }
#  elif defined(__aarch64__)
     static inline void psnip_trap(void) { __asm__ __volatile__(".inst 0xd4200000"); }
#  elif defined(__arm__)
     static inline void psnip_trap(void) { __asm__ __volatile__(".inst 0xe7f001f0"); }
#  elif defined (__alpha__) && !defined(__osf__)
     static inline void psnip_trap(void) { __asm__ __volatile__("bpt"); }
#  elif defined(_54_)
     static inline void psnip_trap(void) { __asm__ __volatile__("ESTOP"); }
#  elif defined(_55_)
     static inline void psnip_trap(void) { __asm__ __volatile__(";\n .if (.MNEMONIC)\n ESTOP_1\n .else\n ESTOP_1()\n .endif\n NOP"); }
#  elif defined(_64P_)
     static inline void psnip_trap(void) { __asm__ __volatile__("SWBP 0"); }
#  elif defined(_6x_)
     static inline void psnip_trap(void) { __asm__ __volatile__("NOP\n .word 0x10000000"); }
#  elif defined(__STDC_HOSTED__) && (__STDC_HOSTED__ == 0) && defined(__GNUC__)
#    define psnip_trap() __builtin_trap()
#  else
#    include <signal.h>
#    if defined(SIGTRAP)
#      define psnip_trap() raise(SIGTRAP)
#    else
#      define psnip_trap() raise(SIGABRT)
#    endif
#  endif
#endif

#if defined(HEDLEY_LIKELY)
#  define PSNIP_DBG_LIKELY(expr) HEDLEY_LIKELY(expr)
#elif defined(__GNUC__) && (__GNUC__ >= 3)
#  define PSNIP_DBG_LIKELY(expr) __builtin_expect(!!(expr), 1)
#else
#  define PSNIP_DBG_LIKELY(expr) (!!(expr))
#endif

#if !defined(PSNIP_NDEBUG) || (PSNIP_NDEBUG == 0)
#  define psnip_dbg_assert(expr) do { \
    if (!PSNIP_DBG_LIKELY(expr)) { \
      psnip_trap(); \
    } \
  } while (0)
#else
#  define psnip_dbg_assert(expr)
#endif

#endif /* !defined(PSNIP_DEBUG_TRAP_H) */

#define DEBUGBREAK_MSG(msg) {                                                                                          \
    Wh_Log(L"Waiting for debugger... %s", L## #msg);                                                                   \
    while (!IsDebuggerPresent())                                                                                       \
        Sleep(10);                                                                                                     \
    Wh_Log(L"Debug breaking... %s", L## #msg);                                                                         \
    psnip_trap();                                                                                                      \
}

#define DEBUGBREAK() DEBUGBREAK_MSG("")

#ifdef _WIN64
    #define FOR_64_32(for64, for32) for64
#else
    #define FOR_64_32(for64, for32) for32
#endif

__forceinline void SafeRelease(IUnknown *punk)
{
    if (punk)
    {
        punk->Release();
    }
}

#define XML(x) L## #x

constexpr wchar_t kLibraryPaneXml[] = XML(
<duixml>
    <stylesheets>
        <style resid="libraryStyle">
            <if class="libContainer">
                <element background="themeable(dtb(CommandModule, 10, 0), window)"/>
            </if>
            <if class="libBackground">
                <element height="54rp" 
                    width="500rp"
                    background="themeable(dtb(CommandModule, 12, 0), argb(0,0,0,0))"/>
            </if>
            <if class="libHeader">
                <element background="argb(0,0,0,0)"/>
            </if>
            <if class="libName">
                <element background="argb(0,0,0,0)"
                    padding="rect(14rp,4rp,0,0)"
                    foreground="themeable(gtc(ControlPanelStyle, 11, 0, 3803), windowtext)"
                    fontsize="14pt"
                    contentalign="middleleft"/>
            </if>
            <if class="libDesc">
                <element background="argb(0,0,0,0)"
                    padding="rect(16rp,1rp,0,0)"
                    foreground="themeable(gtc(ControlPanelStyle, 3, 0, 3803), windowtext)" 
                    contentalign="EndEllipsis"/>
            </if>
            <if class="locationcount">
                <button padding="rect(0,1rp,0,0)" 
                    foreground="themeable(gtc(ControlPanelStyle, 7, 0, 3803), windowtext)"/>
                <if mousefocused="true">
                    <button cursor="hand" 
                        font="gtf(ControlPanelStyle, 7,2)" 
                        foreground="themeable(gtc(ControlPanelStyle, 7, 2, 3803), highlight)"/>
                </if>
            </if>
            <if id="atom(ActionButtonLabel)">
                <Element background="argb(0, 0, 0, 0)" 
                    contentalign="middlecenter"/>
            </if>
            <if id="atom(ActionButtonIcon)">
                <Element background="argb(0, 0, 0, 0)"
                    contentalign="middlecenter"
                    padding="rect(2rp, 0rp, 2rp, 0rp)"/>
            </if>
            <if id="atom(TopViewPrefix)">
                <Element foreground="argb(255, 90, 103, 121)"/>
            </if>
            // TODO: I think something better can be done about this style
            // element.
            <if id="atom(ActionButton)">
                <Button3d background="themeable(dtb(CommandModule, 9, 1), argb(0,0,0,0))"
                    foreground="themeable(gtc(CommandModule, 9, 1, 3803), windowtext)"
                    padding="rect(9rp, 5rp, 9rp, 5rp)"
                    font="gtf(TEXTSTYLE, 4, 0)"/>
                <if mousefocused="true">
                    <Button3d foreground="themeable(gtc(CommandModule, 9, 2, 3803), windowtext)"
                        background="themeable(dtb(CommandModule, 9, 2), dfc(4, 0x0010|0x1000))"/>
                </if>
                <if pressed="true">
                    <Button3d foreground="themeable(gtc(CommandModule, 9, 3, 3803), windowtext)"
                        background="themeable(dtb(CommandModule, 9, 3), dfc(4, 0x0010|0x0200))"/>
                </if>
            </if>
            <if id="atom(MenuButtonGlyph)">
                <Element background="argb(0, 0, 0, 0)"
                    content="6"
                    contentalign="middlecenter"
                    foreground="themeable(gtc(CommandModule, 9, 1, 3803), windowtext)"
                    fontface="Marlett"
                    fontsize="9pt"
                    margin="rect(1rp, 0rp, 0rp, 0rp)"/>
                <if mousefocused="true">
                    <Element foreground="themeable(gtc(CommandModule, 9, 2, 3803), windowtext)"/>
                </if>
                <if mousefocused="true">
                    <Element foreground="themeable(gtc(CommandModule, 9, 3, 3803), windowtext)"/>
                </if>
            </if>
        </style>
    </stylesheets>
    <AJOSplitButton resid="CommandElement" 
        // sheet="TaskButtonStylePlaceholder"
        layout="BorderLayout()" layoutpos="left" active="keyboard" accessible="true" accrole="pane">
        <Button3d id="atom(ActionButton)" layoutpos="right" layout="BorderLayout()" active="mouse" tooltip="true" accessible="true" accrole="pushbutton" accdefaction="Click">
            <Element id="atom(ActionButtonIcon)" layoutpos="left"/>
            <Element id="atom(ActionButtonLabel)" layoutpos="left" shortcut="None"/>
            <Element id="atom(MenuButtonGlyph)" layoutpos="left"/>
        </Button3d>
    </AJOSplitButton>
    <Element resid="LibraryHeader"
        id="atom(LeymonaideLibraryHeaderModule)"
        class="libContainer"

        // The library header defaults to invisible and has its visibility
        // managed programmatically when the DefView is refreshed. When it is
        // invisible, it does not participate in the layout.
        layoutpos="none"

        height="55rp"
        layout="filllayout()"
        sheet="libraryStyle">
        <element layout="flowlayout()" background="argb(0,0,0,0)" layoutpos="top">
            <element class="libBackground" layoutpos="top" />
        </element>
        <element class="libHeader" layout="borderlayout()">
            <element class="libName" id="atom(LibTitle)" layoutpos="top"
                content="Libraries" />
            <element layoutpos="top" background="argb(0,0,0,0)" layout="borderlayout()">
                <element class="libDesc" id="atom(LibDesc)"
                    content="Open a library to see your files and arrange them by folder, date, and other properties."
                    layoutpos="left" />
                <button id="atom(locationcount)" class="locationcount"
                    visible="false"
                    layoutpos="left" />
            </element>
        </element>
        <element id="atom(ArrangeByContainer)" visible="false"
            background="argb(0,0,0,0)"
            layoutpos="right"
            layout="borderlayout()">
            <element layoutpos="right" layout="flowlayout(0,2,2,0)"
                padding="rect(0,0,27rp,0)" id="atom(TopViewControl)">
            </element>
            <element layoutpos="right" id="atom(TopViewPrefix)"
                content="Arrange by:" contentalign="middlecenter" />
        </element>
    </Element>
</duixml>
);

#ifndef COMMA
#define COMMA ,
#endif

/**
 * @brief Defines extra arguments to be passed between two hooked functions.
 *
 * @details
 *     When hooking a function, you cannot change the signature to add more
 *     arguments than the function originally had. As a result, you must pass
 *     state along a different method.
 *
 *     This convention provides an abstraction for using thread local global
 *     variables to pass state to a hooked function.
 *
 *     This function declares a structure, for which a global thread local
 *     pointer will be made, which will be set to the address of a variable
 *     (usually on the stack of the setter) 
 *
 * @example
 *     DEFINE_TRANSITION_EXTRA_ARGS(FunctionA, FunctionB, {
 *         SharedState sharedState;
 *         int counter;
 *     })
 */
#define DEFINE_TRANSITION_EXTRA_ARGS(from, to, body)                           \
    struct s## from ## __to__ ## to ## __vars body;                            \
    thread_local s## from ## __to__ ## to ## __vars * g_inst## from            \
        ## __to__ ## to ## __vars = nullptr

/**
 * @brief
 *     Defines extra arguments to be passed between two hooked functions. This
 *     variant of the macro sets up the transition state to be thread global,
 *     which is required if the function calls cross thread boundaries.
 *
 * @details
 *     When hooking a function, you cannot change the signature to add more
 *     arguments than the function originally had. As a result, you must pass
 *     state along a different method.
 *
 *     This convention provides an abstraction for using thread local global
 *     variables to pass state to a hooked function.
 *
 *     This function declares a structure, for which a global thread local
 *     pointer will be made, which will be set to the address of a variable
 *     (usually on the stack of the setter) 
 *
 *     Please note that when using this thread global variant, you are
 *     responsible for managing synchronization yourself.
 *
 * @example
 *     DEFINE_TRANSITION_EXTRA_ARGS_THREAD_GLOBAL(FunctionA, FunctionB, {
 *         SharedState sharedState;
 *         int counter;
 *     })
 */
#define DEFINE_TRANSITION_EXTRA_ARGS_THREAD_GLOBAL(from, to, body)             \
    struct s## from ## __to__ ## to ## __vars body;                            \
    s## from ## __to__ ## to ## __vars * g_inst## from                         \
        ## __to__ ## to ## __vars = nullptr

/**
 * @brief Sets hook use extra arguments to a user defined value.
 *
 * @details
 *     The value should be set to nullptr once the extra arguments are no longer
 *     needed.
 */
#define SET_TRANSITION_EXTRA_ARGS_VALUE(from, to, value)                       \
    g_inst## from ## __to__ ## to ## __vars = value

/**
 * @brief Declares the value of an argument for SET_TRANSITION_EXTRA_ARGS.
 */
#define TRANSITION_EXTRA_ARG(expression) .expression,

/**
 * @brief Sets hook use extra arguments.
 *
 * @warning
 *     Please note that the body must use the COMMA macro instead of a comma
 *     directly due to a limitation with C preprocessor macros, or use the
 *     TRANSITION_EXTRA_ARG macro.
 *
 * @example
 *     SET_TRANSITION_EXTRA_ARGS(FunctionA, FunctionB, {
 *         TRANSITION_EXTRA_ARG(sharedState = sharedState)
 *         TRANSITION_EXTRA_ARG(counter = counter)
 *     });
 */
#define SET_TRANSITION_EXTRA_ARGS(from, to, body)                              \
    struct ScopeExit {                                                         \
        __forceinline ~ScopeExit() {                                           \
            g_inst## from ## __to__ ## to ## __vars = nullptr;                 \
        }                                                                      \
    } __transition_extra_args_scope_exit_helper;                               \
    s## from ## __to__ ## to ## __vars __transition_extra_args = body;         \
    SET_TRANSITION_EXTRA_ARGS_VALUE(from, to, &__transition_extra_args)

/**
 * @brief
 *     Sets hook use extra arguments with allocation on the heap. This can be
 *     used for child to parent data transfers.
 *
 * @warning
 *     Please note that the body must use the COMMA macro instead of a comma
 *     directly due to a limitation with C preprocessor macros, or use the
 *     TRANSITION_EXTRA_ARG macro.
 *
 * @example
 *     SET_TRANSITION_EXTRA_ARGS_ALLOC(FunctionA, FunctionB, {
 *         TRANSITION_EXTRA_ARG(sharedState = sharedState)
 *         TRANSITION_EXTRA_ARG(counter = counter)
 *     });
 */
#define SET_TRANSITION_EXTRA_ARGS_ALLOC(from, to, body)                        \
{                                                                              \
    s## from ## __to__ ## to ## __vars *__transition_extra_args =              \
        new s## from ## __to__ ## to ## __vars;                                \
    *__transition_extra_args = body;                                           \
    SET_TRANSITION_EXTRA_ARGS_VALUE(from, to, __transition_extra_args);        \
}

/**
 * @brief Frees arguments allocated with SET_TRANSITION_EXTRA_ARGS_ALLOC.
 */
#define FREE_TRANSITION_EXTRA_ARGS(from, to)                                   \
{                                                                              \
    delete GET_TRANSITION_EXTRA_ARGS(from, to);                                \
    SET_TRANSITION_EXTRA_ARGS_VALUE(from, to, nullptr);                        \
}

/**
 * @brief Gets hook use extra arguments.
 *
 * @example
 *     auto extraArgs = GET_TRANSITION_EXTRA_ARGS(FunctionA, FunctionB);
 *     auto sharedState = extraArgs->sharedState;
 */
#define GET_TRANSITION_EXTRA_ARGS(from, to)                                    \
    RUNTIME_ASSERT(g_inst## from ## __to__ ## to ## __vars,                    \
        "Make sure that you set the arguments using SET_TRANSITION_EXTRA_ARGS" \
        "first.")

/**
 * @brief Determines if hook use extra arguments exist.
 */
#define HAS_TRANSITION_EXTRA_ARGS(from, to)                                    \
    (nullptr != g_inst## from ## __to__ ## to ## __vars)

// Copied from Aerexplorer.
// https://github.com/ramensoftware/windhawk-mods/blob/99d558b204a080b3f1974b47289ae94c205571e9/mods/aerexplorer.wh.cpp#L798-L810
[[nodiscard]] BYTE ParseHexChar(WCHAR c)
{
    if (c >= L'0' && c <= L'9')
        return c - L'0';

    if (c >= 'A' && c <= 'F')
        return c - ('A' - 0xA);

    if (c >= 'a' && c <= 'f')
        return c - ('a' - 0xA);

    return 0;
}

// Copied partially from Aerexplorer.
// https://github.com/ramensoftware/windhawk-mods/blob/99d558b204a080b3f1974b47289ae94c205571e9/mods/aerexplorer.wh.cpp#L812
[[nodiscard]] const Translations &GetUIStrings()
{
    ULONG ulNumLanguages;
    WCHAR szLanguages[MAX_PATH];
    DWORD cchLanguages = ARRAYSIZE(szLanguages);
    szLanguages[0] = L'\0';
    GetThreadPreferredUILanguages(MUI_LANGUAGE_ID, &ulNumLanguages, szLanguages, &cchLanguages);

    const Translations *primaryMatch = nullptr;
    const Translations *fullMatch = nullptr;

    LANGID langid = 0;
    for (ULONG i = 0; i < ulNumLanguages; i++)
    {
        LPWSTR pszLang = szLanguages + (i * 5);
        langid = ParseHexChar(pszLang[0]) << 12
            | ParseHexChar(pszLang[1]) << 8
            | ParseHexChar(pszLang[2]) << 4
            | ParseHexChar(pszLang[3]);

        if (langid == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US))
            return kStrings[kTranslationsEnUsIndex];

        for (UINT i = 0; i < ARRAYSIZE(kStrings); i++)
        {
            const Translations *current = &kStrings[i];

            if (PRIMARYLANGID(current->langId) == PRIMARYLANGID(langid))
            {
                primaryMatch = current;
            }

            if (current->langId == langid)
            {
                fullMatch = current;
                break;
            }
        }

        if (primaryMatch)
            break;
    }

    if (fullMatch)
        return *fullMatch;
    if (primaryMatch)
        return *primaryMatch;
    
    return kStrings[kTranslationsEnUsIndex];
}

#define UILIB_API // __declspec(dllimport)

// These min/max macros are required for the DUI headers copied into here.
// Windhawk doesn't come with the headers it expects.
#define min(a, b) (a > b ? a : b)
#define max(a, b) (a < b ? a : b)

// ============================================================================
// ======================= THE LARGE DUI HEADERS ZONE =========================
// ============================================================================
//
// !!!!!!!!!  Search for "/END DIRECTUI HEADERS" to skip this section. !!!!!!!!!
//
//    The following section contains DirectUI headers copied from the
//    World Windows Federation's DirectUI headers project. It is very
//    verbose and none of it is original code.
//
//
//    The original code can be found here:
//    - https://github.com/world-windows-federation/dui70
//
//    These headers were last updated on:
//    - 2025-12-03 07:26 JST
//
//    Revision hash: 852685d90dec166b79ff80c2087c1cc74fbe0f82
//
//
//    My utmost gratitude to AllieTheFox and Amrsatrio for this wonderful
//    project.
//
// ============================================================================


#define _ASSERT(x)
#define _ASSERTE(x)
#define DUI_ASSERT_EXPR(x, msg)

// ATTENTION: Manually defined stub types.
namespace DirectUI
{
    DECLARE_HANDLE(HGADGET); // Congruent with DUser/DUser.h
    class Surface {};
    class NavReference {};
    class IDuiBehavior {};
    class GMSG {};
    class EventMsg {};
    class ISharedBitmap {};
    class StyleSheet {};
    class Expression {};
}

// Layout position enums. These are sourced from the following files:
// world-windows-federation/dui70/DirectUI/Core/Layout.h
// world-windows-federation/dui70/DirectUI/Layout/BorderLayout.h
namespace DirectUI
{
    enum LayoutPos
    {
        LP_None     = -3,
        LP_Absolute = -2,
        LP_Auto     = -1,
    };

    enum BorderLayoutPos
	{
		BLP_Left   = 0,
		BLP_Top    = 1,
		BLP_Right  = 2,
		BLP_Bottom = 3,
		BLP_Client = 4,
	};
}

// world-windows-federation/dui70/DirectUI/Base/Alloc.h
namespace DirectUI
{
	inline void* HAlloc(SIZE_T cbBlockSize)
	{
		return HeapAlloc(GetProcessHeap(), 0, cbBlockSize);
	}

	inline void* HReAlloc(void* p, SIZE_T s)
	{
		return HeapReAlloc(GetProcessHeap(), 0, p, s);
	}

	inline void HFree(void* pv)
	{
		HeapFree(GetProcessHeap(), 0, pv);
	}

	template <typename T>
	T* HNewAndZero()
	{
		T* p = (T*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(T));
		if (p)
			new (p) T();
		return p;
	}

	template <typename T>
	T* HNew()
	{
		return HNewAndZero<T>();
	}

	template <typename T>
	void HDelete(T* p)
	{
		p->~T();
		HFree(p);
	}
}

// world-windows-federation/dui70/DirectUI/Base/DynamicArray.h
namespace DirectUI
{
	// exported for int
	template <typename T>
	class SafeArrayAccessor
	{
		SAFEARRAY* _pSafeArray;
		int _count;
		T* _pData;

	public:
		SafeArrayAccessor()
			: _pSafeArray(nullptr)
			, _count(0)
			, _pData(nullptr)
		{
		}

	private:
		SafeArrayAccessor(const SafeArrayAccessor&) = delete;
		void operator=(const SafeArrayAccessor&) = delete;

	public:
		~SafeArrayAccessor()
		{
			SafeArrayUnaccessData(_pSafeArray);
		}

		HRESULT Access(SAFEARRAY* pSafeArray, VARTYPE vtExpected)
		{
			_pSafeArray = pSafeArray;

			if (SafeArrayGetDim(pSafeArray) != 1)
				return E_FAIL;

			VARTYPE actualType;
			HRESULT hr = SafeArrayGetVartype(_pSafeArray, &actualType);
			if (SUCCEEDED(hr))
				if (SUCCEEDED(hr))
				{
					if (actualType != vtExpected)
						return E_FAIL;

					LONG lb;
					hr = SafeArrayGetLBound(_pSafeArray, 1, &lb);
					if (SUCCEEDED(hr))
					{
						LONG ub;
						hr = SafeArrayGetUBound(_pSafeArray, 1, &ub);
						if (SUCCEEDED(hr))
						{
							_count = ub - lb + 1;
							hr = SafeArrayAccessData(_pSafeArray, (void**)&_pData);
						}
					}
				}

			return hr;
		}

		int Count() { return _count; }
		operator T*() { return _pData; }
	};

	class UILIB_API CritSecLock
	{
	public:
		CritSecLock(CRITICAL_SECTION* pacs);
		~CritSecLock();

		void Unlock();

	private:
		CRITICAL_SECTION* _pacs;
	};

	template <typename T>
	class DoubleAllocationPolicy
	{
	public:
		struct HeapT
		{
			T* _pData;
			UINT _uCapacity;
		};

		static UINT GetCapacity(const HeapT __unaligned& heap, UINT uRequiredCapacity)
		{
			return heap._uCapacity;
		}

		static void SetCapacity(HeapT __unaligned* pHeap, UINT uCapacity)
		{
			pHeap->_uCapacity = uCapacity;
		}

		static UINT NewCapacity(UINT uRequiredCapacity)
		{
			return uRequiredCapacity;
		}

		static UINT NewCapacity(const HeapT __unaligned& heap, UINT uRequiredCapacity)
		{
			UINT uNewCapacity;
			if (SUCCEEDED(UIntMult(2, heap._uCapacity, &uNewCapacity)))
			{
				return max(uRequiredCapacity, uNewCapacity);
			}
			return uRequiredCapacity;
		}
	};

	// ReSharper disable once CppClassNeedsConstructorBecauseOfUninitializedMember
	template <typename T, typename TAllocationPolicy, int MinInplaceCapacity = 1, int MinHeapCapacity = 0>
	class DynamicArrayBase
	{
		using HeapT = typename TAllocationPolicy::HeapT;

	public:
		static const UINT INPLACE_BUFFER_SIZE_CALC = sizeof(HeapT) / sizeof(T);
		static const UINT INPLACE_BUFFER_SIZE = max(MinInplaceCapacity, INPLACE_BUFFER_SIZE_CALC);
		static const UINT MAX_DYNAMIC_ARRAY_SIZE = 0xFFFFFFF;

		void Destroy()
		{
			Release();
			HFree(this);
		}

		void Release()
		{
			if (_fHeapBuffer)
			{
				CHeapBuffer_Release(this);
			}

			Reset();
		}

		void DestroyDeep()
		{
			T* pBuffer = Buffer();
			for (UINT i = 0; i < _uSize; i++)
			{
				HDelete(pBuffer[i]);
			}
		}

		static HRESULT Create(bool fZeroData, DynamicArrayBase** ppArray)
		{
			return Create(0, fZeroData, ppArray);
		}

		static HRESULT Create(UINT uCapacity, bool fZeroData, DynamicArrayBase** ppArray)
		{
			DynamicArrayBase* p = HNew<DynamicArrayBase>();
			if (!p)
				return E_OUTOFMEMORY;

			HRESULT hr = p->Initialize(uCapacity, fZeroData);
			if (SUCCEEDED(hr))
			{
				*ppArray = p;
				hr = S_OK;
			}
			else
			{
				p->Destroy();
			}

			return hr;
		}

		HRESULT Initialize(bool fZeroData)
		{
			return Initialize(0, fZeroData);
		}

		HRESULT Initialize(UINT uCapacity, bool fZeroData)
		{
			HRESULT hr = S_OK;

			Reset();
			_fZeroData = fZeroData;
			_fImmutable = false;
			_Heap = {};

			if (uCapacity > MAX_DYNAMIC_ARRAY_SIZE)
			{
				hr = E_INVALIDARG;
			}
			else if (uCapacity > INPLACE_BUFFER_SIZE)
			{
				SwitchToHeap(uCapacity);
			}

			return hr;
		}

		HRESULT SizeIncrement(UINT uSize, UINT* puNewSize)
		{
			HRESULT hr;

			UINT uNewSize = uSize + 1;
			if (uNewSize >= uSize && uNewSize <= MAX_DYNAMIC_ARRAY_SIZE)
			{
				*puNewSize = uNewSize;
				hr = S_OK;
			}
			else
			{
				hr = INTSAFE_E_ARITHMETIC_OVERFLOW;
				*puNewSize = -1;
			}

			return hr;
		}

		HRESULT InsertPtr(UINT uIndex, T** ppNewItem)
		{
			UINT uNewSize;
			HRESULT hr = SizeIncrement(_uSize, &uNewSize);
			if (SUCCEEDED(hr))
			{
				if (!_fHeapBuffer && _uSize == INPLACE_BUFFER_SIZE)
				{
					hr = SwitchToHeap(uNewSize);
				}

				if (SUCCEEDED(hr))
				{
					T* pNewItem;
					if (_fHeapBuffer)
					{
						hr = CHeapBuffer_InsertPtr(this, uIndex, uNewSize, &pNewItem);
					}
					else
					{
						hr = CInplaceBuffer_InsertPtr(this, uIndex, uNewSize, &pNewItem);
					}

					if (SUCCEEDED(hr))
					{
						memmove(pNewItem + 1, pNewItem, sizeof(T) * (_uSize - uIndex));
						_uSize = uNewSize;
						if (_fZeroData)
						{
							*pNewItem = {};
						}
						*ppNewItem = pNewItem;
					}
				}
			}

			return hr;
		}

		HRESULT Reserve(UINT uCapacity)
		{
			HRESULT hr = S_OK;

			if (_fHeapBuffer)
			{
				hr = CHeapBuffer_Reserve(this, uCapacity);
			}
			else if (uCapacity > INPLACE_BUFFER_SIZE)
			{
				hr = SwitchToHeap(uCapacity);
			}

			return hr;
		}

		HRESULT Add(T tItem)
		{
			return Insert(_uSize, tItem);
		}

		// Assumed function body
		HRESULT AddPtr(T** ppNewItem, UINT* puIndex)
		{
			if (puIndex)
				*puIndex = -1;

			HRESULT hr = InsertPtr(_uSize, ppNewItem);
			if (SUCCEEDED(hr))
			{
				if (puIndex)
					*puIndex = _uSize - 1;
			}

			return hr;
		}

		HRESULT AddPtr(T** ppNewItem)
		{
			return AddPtr(ppNewItem, nullptr);
		}

		HRESULT Insert(UINT uIndex, T tItem)
		{
			T* pNewItem;
			HRESULT hr = InsertPtr(uIndex, &pNewItem);
			if (SUCCEEDED(hr))
			{
				*pNewItem = tItem;
			}

			return hr;
		}

		void SetItem(UINT uIndex, T tItem)
		{
			*GetItemPtr(uIndex) = tItem;
		}

		T GetItem(UINT uIndex) const
		{
			return *GetItemPtr(uIndex);
		}

		T* GetItemPtr(UINT uIndex)
		{
			DUI_ASSERT_EXPR(uIndex < _uSize, "DynamicArray index out of bounds");
			return Buffer() + uIndex;
		}

		const T* GetItemPtr(UINT uIndex) const
		{
			DUI_ASSERT_EXPR(uIndex < _uSize, "DynamicArray index out of bounds");
			return Buffer() + uIndex;
		}

		UINT GetIndexPtr(T* ptItem) const
		{
			return GetIndexOf(*ptItem);
		}

		int GetIndexOf(T tItem) const
		{
			const T* pBuffer = Buffer();
			for (UINT i = 0; i < _uSize; i++)
			{
				if (pBuffer[i] == tItem)
				{
					return i;
				}
			}

			return -1;
		}

		UINT GetSize() const
		{
			return _uSize;
		}

		UINT GetCapacity() const
		{
			return _fHeapBuffer ? CHeapBuffer_GetCapacity(this) : CInplaceBuffer_GetCapacity(this);
		}

		void Remove(UINT uIndex)
		{
			Remove(uIndex, 1);
		}

		void Remove(UINT uIndex, UINT cItems)
		{
			if (_uSize - uIndex != cItems)
			{
				T* pBuffer = Buffer();
				memmove(pBuffer + uIndex, pBuffer + (uIndex + cItems), sizeof(T) * (_uSize - uIndex - cItems));
			}
			_uSize -= cItems;
		}

		void Reset()
		{
			_uSize = 0;
			_fHeapBuffer = false;
		}

		bool IsEqual(const DynamicArrayBase* pOther) const
		{
			if (!pOther)
				return false;

			if (_uSize != pOther->_uSize)
				return false;

			const T* pBuffer = Buffer();
			const T* pOtherBuffer = pOther->Buffer();
			return !pBuffer || memcmp(pBuffer, pOtherBuffer, sizeof(T) * _uSize) == 0;
		}

		HRESULT Clone(DynamicArrayBase** ppClone) const
		{
			*ppClone = nullptr;
			HRESULT hr;

			DynamicArrayBase* p = HNew<DynamicArrayBase>();
			if (!p)
				return E_OUTOFMEMORY;

			p->Reset();
			p->_fZeroData = false;
			p->_fImmutable = false;
			p->_fZeroData = _fZeroData;
			p->_Heap = {};

			if (p->_fHeapBuffer)
			{
				hr = CHeapBuffer_Reserve(p, _uSize);
			}
			else if (_uSize > INPLACE_BUFFER_SIZE)
			{
				hr = p->SwitchToHeap(_uSize);
			}
			else
			{
				hr = S_OK;
			}

			if (SUCCEEDED(hr))
			{
				const T* pBuffer = Buffer();
				if (pBuffer)
				{
					memcpy(p->Buffer(), pBuffer, sizeof(T) * _uSize);
				}
				*ppClone = p;
				p->_uSize = _uSize;
			}
			else
			{
				p->Destroy();
			}

			return hr;
		}

		HRESULT SetSize(UINT uCapacity)
		{
			HRESULT hr = Reserve(uCapacity);
			if (SUCCEEDED(hr))
			{
				_uSize = uCapacity;
			}

			return hr;
		}

		typedef int (__cdecl *QSORTCMP)(const void*, const void*);

		void Sort(QSORTCMP fpCmp)
		{
			if (_uSize)
			{
				qsort(Buffer(), _uSize, sizeof(T), fpCmp);
			}
		}

		void MakeImmutable()
		{
#ifdef _DEBUG
			_fImmutable = true;
#endif
		}

		void MakeWritable()
		{
#ifdef _DEBUG
			_fImmutable = false;
#endif
		}

		bool Find(const T& item, UINT* piFound)
		{
			if (piFound)
				*piFound = -1;

			bool fFound = false;

			T* pBuffer = Buffer();
			for (UINT i = 0; i < _uSize; i++)
			{
				if (pBuffer[i] == item)
				{
					fFound = true;
					if (piFound)
						*piFound = i;
					break;
				}
			}

			return fFound;
		}

		template <typename TFunc>
		bool Find(UINT* piFound, const TFunc& func)
		{
			if (piFound)
				*piFound = -1;

			bool fFound = false;

			T* pBuffer = Buffer();
			for (UINT i = 0; i < _uSize; i++)
			{
				if (func(pBuffer[i]))
				{
					fFound = true;
					if (piFound)
						*piFound = i;
					break;
				}
			}

			return fFound;
		}

	private:
		HRESULT SwitchToHeap(UINT uMinCapacity)
		{
			UINT uInitial = TAllocationPolicy::NewCapacity(max(uMinCapacity, MinHeapCapacity));

			UINT cbToAlloc;
			HRESULT hr = UIntMult(sizeof(T), uInitial, &cbToAlloc);
			if (SUCCEEDED(hr))
			{
				T* pNewBuffer = (T*)HAlloc(cbToAlloc);
				hr = pNewBuffer ? S_OK : E_OUTOFMEMORY;
				if (SUCCEEDED(hr))
				{
					memcpy(pNewBuffer, Buffer(), sizeof(T) * _uSize);
					_fHeapBuffer = true;
					_Heap._pData = pNewBuffer;
					TAllocationPolicy::SetCapacity(&_Heap, uInitial);
				}
			}

			return hr;
		}

		static void CHeapBuffer_Release(DynamicArrayBase* pThis)
		{
			if (pThis->_Heap._pData)
			{
				HFree(pThis->_Heap._pData);
				pThis->_Heap._pData = nullptr;
			}
			TAllocationPolicy::SetCapacity(&pThis->_Heap, 0);
		}

		static HRESULT CHeapBuffer_Reserve(DynamicArrayBase* pThis, UINT uMinCapacity)
		{
			HRESULT hr = S_OK;

			if (uMinCapacity > TAllocationPolicy::GetCapacity(pThis->_Heap, pThis->_uSize))
			{
				UINT cbToAlloc;
				hr = UIntMult(sizeof(T), TAllocationPolicy::NewCapacity(pThis->_Heap, uMinCapacity), &cbToAlloc);
				if (SUCCEEDED(hr))
				{
					if (pThis->_Heap._pData)
					{
						T* pNewData = (T*)HReAlloc(pThis->_Heap._pData, cbToAlloc);
						if (!pNewData)
							return E_OUTOFMEMORY;

						pThis->_Heap._pData = pNewData;
					}
					else
					{
						pThis->_Heap._pData = (T*)HAlloc(cbToAlloc);
						if (!pThis->_Heap._pData)
							return E_OUTOFMEMORY;
					}
				}
			}

			return hr;
		}

		static HRESULT CHeapBuffer_InsertPtr(DynamicArrayBase* pThis, UINT uIndex, UINT uNewSize, T** ppNewItem)
		{
			HRESULT hr = CHeapBuffer_Reserve(pThis, uNewSize);
			if (SUCCEEDED(hr))
			{
				*ppNewItem = &pThis->_Heap._pData[uIndex];
			}
			return hr;
		}

		static UINT CHeapBuffer_GetCapacity(DynamicArrayBase* pThis)
		{
			return pThis->_Heap._uCapacity;
		}

		static void CInplaceBuffer_Release(DynamicArrayBase* pThis)
		{
			// No-op
		}

		static HRESULT CInplaceBuffer_Reserve(DynamicArrayBase* pThis, UINT uMinCapacity)
		{
			if (uMinCapacity > INPLACE_BUFFER_SIZE)
			{
				_ASSERTE(false);
			}

			return S_OK;
		}

		static HRESULT CInplaceBuffer_InsertPtr(DynamicArrayBase* pThis, UINT uIndex, UINT uNewSize, T** ppNewItem)
		{
			if (uNewSize > INPLACE_BUFFER_SIZE)
			{
				_ASSERTE(false);
			}

			*ppNewItem = &pThis->_Inplace[uIndex];
			return S_OK;
		}

		static UINT CInplaceBuffer_GetCapacity(DynamicArrayBase* pThis)
		{
			return INPLACE_BUFFER_SIZE;
		}

		T* Buffer()
		{
			if (_fHeapBuffer)
			{
				return _Heap._pData;
			}
			else
			{
				if (_uSize > INPLACE_BUFFER_SIZE)
					_ASSERT(false);
				return _Inplace;
			}
		}

		const T* Buffer() const
		{
			if (_fHeapBuffer)
			{
				return _Heap._pData;
			}
			else
			{
				if (_uSize > INPLACE_BUFFER_SIZE)
					_ASSERT(false);
				return _Inplace;
			}
		}

		UINT _uSize : 28; // bits=0-27 mask=0xFFFFFFF
		UINT _fHeapBuffer : 1; // bits=28-28 mask=0x10000000 aka=((*(_DWORD*)this >> 28) & 1) != 0
		UINT _fZeroData : 1; // bits=29-29 mask=0x20000000 aka=((*(_DWORD*)this >> 29) & 1) != 0
		UINT _fImmutable : 1; // bits=30-30 mask=0x40000000 aka=((*(_DWORD*)this >> 30) & 1) != 0

		// _fHeapBuffer | _fZeroData | _fImmutable is 0x70000000

		union
		{
#ifdef _WIN64
#include <pshpack8.h>
#else
#include <pshpack4.h>
#endif
			// ReSharper disable once CppUninitializedNonStaticDataMember
			typename TAllocationPolicy::HeapT _Heap;
			// ReSharper disable once CppUninitializedNonStaticDataMember
			T _Inplace[INPLACE_BUFFER_SIZE];
#include <poppack.h>
		};
	};

	template <typename T, int MinHeapCapacity = 0>
	class DynamicArray : public DynamicArrayBase<T, DoubleAllocationPolicy<T>, 1, MinHeapCapacity>
	{
		using BaseT = DynamicArrayBase<T, DoubleAllocationPolicy<T>, 1, MinHeapCapacity>;

	public:
		~DynamicArray()
		{
			BaseT::Release();
		}

		void Destroy()
		{
			BaseT::Destroy();
		}

		static HRESULT Create(bool fZeroData, DynamicArray** ppArray)
		{
			return Create(0, fZeroData, ppArray);
		}

		static HRESULT Create(UINT uCapacity, bool fZeroData, DynamicArray** ppArray)
		{
			BaseT* pTmp;
			HRESULT hr = BaseT::Create(uCapacity, fZeroData, &pTmp);

			if (SUCCEEDED(hr))
			{
				*ppArray = (DynamicArray*)pTmp;
			}
			else
			{
				*ppArray = nullptr;
			}

			return hr;
		}

		HRESULT Clone(DynamicArray** ppClone) const
		{
			BaseT* pTmp;
			HRESULT hr = BaseT::Clone(&pTmp);

			if (SUCCEEDED(hr))
			{
				*ppClone = (DynamicArray*)pTmp;
			}
			else
			{
				*ppClone = nullptr;
			}

			return hr;
		}
	};

	template <class T>
	class UiaArray : DynamicArray<T>
	{
	public:
	};
}

// world-windows-federation/dui70/DirectUI/Types.h
typedef class UID (WINAPI *UIDPROC)();

class UID
{
public:
	// user defined ctor
	// to enable correct return by outptr sematics
	// https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170#return-values
	UID() : _address(nullptr)
	{
	}

	UID(const BYTE* address) : _address(address)
	{
	}

	UID(UIDPROC proc) : _address(proc()._address)
	{
	}

	const BYTE* _address;
#if 1 // MODMOD: MSVC will pass this as an argument on the rcx register on x86,
      // as it inserts arguments for returned structures. Clang does not do this
      // for sufficiently small structures, so padding must be added to force it
      // to use an argument and avoid an access violation.
    const void *_padding;
    const void *_padding2;
#endif // MODMOD
};

inline bool operator==(const UID& lhs, const UID& rhs)
{
	return lhs._address == rhs._address;
}

inline bool operator==(const UID& lhs, const UIDPROC& rhs)
{
	return lhs._address == rhs()._address;
}

//forward declares
namespace DirectUI
{
	template <typename T, typename U>
	struct _IsSame
	{
		static constexpr bool Value = false;
	};

	template <typename T>
	struct _IsSame<T, T>
	{
		static constexpr bool Value = true;
	};

#if 0 // MODMOD: Not applicable to the mod as dui70 cannot be statically linked.
	static_assert(_IsSame<wchar_t, unsigned short>::Value,
		"Please disable \"Treat WChar_t As Built in Type\" in the project settings. "
		"Disabling this is required as dui70.dll is compiled with this setting disabled, "
		"otherwise linking to dui70.dll functions using WCHAR will fail.");
#endif


	typedef class ProviderProxy* (CALLBACK *PfnCreateProxy)(class Element*);
	typedef int MethodId;


	struct ThemeChangedEvent
	{

	};

	class ElementProvider;
	class InvokeHelper;
	class Value;
	struct PropertyInfo;
}

// world-windows-federation/dui70/DirectUI/Extensions/Misc.h
namespace DirectUI
{
	enum DUSER_MSG_FLAG : UINT32
	{
		GMF_DIRECT = 0x00000000, // OnMessage
		GMF_ROUTED = 0x00000001, // PreviewMessage
		GMF_BUBBLED = 0x00000002, // PostMessage
		GMF_EVENT = 0x00000003, // Message -> Event
		GMF_DESTINATION = 0x00000003, // Message reach dest (same as event)
	};

	enum DUSER_INPUT_DEVICE : UINT32
	{
		GINPUT_MOUSE = 0,
		GINPUT_KEYBOARD = 1,
		GINPUT_JOYSTICK = 2,
	};

	enum DUSER_INPUT_CODE : UINT32
	{
		GMOUSE_MOVE = 0,
		GMOUSE_DOWN = 1,
		GMOUSE_UP = 2,
		GMOUSE_DRAG = 3,
		GMOUSE_HOVER = 4,
		GMOUSE_WHEEL = 5,
		GMOUSE_MAX = 5,

		GBUTTON_NONE = 0,
		GBUTTON_LEFT = 1,
		GBUTTON_RIGHT = 2,
		GBUTTON_MIDDLE = 3,
		GBUTTON_MAX = 3,
	};

	// bitflags
	enum DUSER_INPUT_MODIFIERS : UINT32
	{
		GMODIFIER_NONE = 0x00000000,

		GMODIFIER_LCONTROL = 0x00000001,
		GMODIFIER_RCONTROL = 0x00000002,
		GMODIFIER_LSHIFT = 0x00000004,
		GMODIFIER_RSHIFT = 0x00000008,
		GMODIFIER_LALT = 0x00000010,
		GMODIFIER_RALT = 0x00000020,
		GMODIFIER_LBUTTON = 0x00000040,
		GMODIFIER_RBUTTON = 0x00000080,
		GMODIFIER_MBUTTON = 0x00000100,

		GMODIFIER_CONTROL = (GMODIFIER_LCONTROL | GMODIFIER_RCONTROL),
		GMODIFIER_SHIFT = (GMODIFIER_LSHIFT | GMODIFIER_RSHIFT),
		GMODIFIER_ALT = (GMODIFIER_LALT | GMODIFIER_RALT),
	};

	enum TOUCHTOOLTIP_CREATE_FLAGS
	{
		TTTCF_DEFAULT = 0x0,
		TTTCF_DESKTOP_DPI = 0x1,
		TTTCF_CONSTRAIN_TO_WORKSPACE = 0x2,
		TTTCF_CONSTRAIN_TO_MONITOR = 0x4,
	};

	enum TOUCHTOOLTIP_OPTION_FLAGS
	{
		TTTOF_DEFAULT = 0x0,
		TTTOF_LAST_LINE_SUBTITLE = 0x1,
		TTTOF_SLIDER = 0x2,
		TTTOF_NO_WRAP = 0x4,
		TTTOF_NO_UIA_OPENED_EVENT = 0x8,
		TTTOF_SCALE_WITH_OWNER = 0x10,
	};

	enum TOUCHTOOLTIP_INPUT
	{
		TTTI_PROGRAMMATIC = 0,
		TTTI_KEYBOARD = 1,
		TTTI_MOUSE = 2,
		TTTI_POINTER = 3,
		TTTI_COUNT = 4,
	};

	enum TOUCHTOOLTIP_PLACEMENT
	{
		TTTP_ABOVE = 0,
		TTTP_BELOW = 1,
		TTTP_LEFT = 2,
		TTTP_RIGHT = 3,
		TTTP_COUNT = 4,
	};

	enum TOUCHTOOLTIP_TYPE
	{
		TTTT_TEXT = 0,
		TTTT_RICH = 1,
		TTTT_COUNT = 2,
	};

	enum TOUCHTOOLTIP_DELAY
	{
		TTTD_NORMAL = 0,
		TTTD_RESHOW = 1,
		TTTD_COUNT = 2,
	};

	enum TOUCHTOOLTIP_LAYOUT_DIRECTION
	{
		TTTLD_INHERIT = 0,
		TTTLD_LTR = 1,
		TTTLD_RTL = 2,
		TTTLD_COUNT = 3,
	};

	enum ActiveState
	{
		AS_HIDDEN = 0,
		AS_REST = 1,
		AS_MOUSE = 2,
		AS_PAN = 3,
	};
} // namespace DirectUI

// world-windows-federation/dui70/DirectUI/Core/Event.h
#if 1 // MODMOD: Forward declare.
namespace DirectUI
{
    class Element;
}
#endif // MODMOD
namespace DirectUI
{
	struct Event
	{
		Element* peTarget;
		UID uidType;
		bool fHandled;
		DUSER_MSG_FLAG nStage;
		bool fUIAHandled;
	};

	struct InputEvent
	{
		Element* peTarget;
		bool fHandled;
		DUSER_MSG_FLAG nStage;
		DUSER_INPUT_DEVICE nDevice;
		DUSER_INPUT_CODE nCode;
		DUSER_INPUT_MODIFIERS uModifiers;
	};

	struct PointerEvent : InputEvent
	{
		POINT ptClientPxl;
		UINT nPointerID;
		BOOL fPrimary;
	};

	struct PointerTapEvent : PointerEvent
	{
		UINT cTaps;
		BOOL fPressAndTap;
		BOOL fWithin;
		UINT nFlags;
		BOOL fPressAndHold;
	};

	struct PointerEnterEvent : PointerEvent
	{
	};

	struct PointerLeaveEvent : PointerEvent
	{
	};

	struct PointerCancelEvent : PointerEvent
	{
		UINT nCancelReason;
	};

	struct PointerManipulationEvent : PointerEvent
	{
		UINT nBeginDuringEnd;
		SIZE szOffsetFromPanStart;
		float fltZoom;
		float fltExpansion;
		float fltRotation;
		UINT nFlags;
	};

	struct PointerDragEvent : PointerEvent
	{
		SIZE sizeDelta;
		BOOL fWithin;
	};

	struct MouseEvent : InputEvent
	{
		POINT ptClientPxl;
		BYTE bButton;
		UINT nFlags;
	};

	struct MouseWheelEvent : MouseEvent
	{
		short sWheel;
	};

	struct MouseDragEvent : MouseEvent
	{
		SIZE sizeDelta;
		BOOL fWithin;
	};

	struct MouseClickEvent : MouseEvent
	{
		UINT cClicks;
	};

	struct KeyboardEvent : InputEvent
	{
		WCHAR ch;
		WORD cRep;
		WORD wFlags;
	};

	struct KeyboardNavigateEvent : Event
	{
		int iNavDir;
		bool fSetFocus;
	};

	struct AnimateScrollEvent : Event
	{
		int dDistance;
		bool fVertical;
	};
}

// world-windows-federation/dui70/DirectUI/Interfaces.h
// MODMOD: Only some declarations were copied over.
#if 1 // MODMOD: Forward declare.
namespace DirectUI
{
    class Element;
    class PropertyInfo;
    class Value;
}
#endif // MODMOD
namespace DirectUI
{
    DECLARE_INTERFACE(IElementListener)
	{
		virtual void OnListenerAttach(Element* peFrom) = 0;
		virtual void OnListenerDetach(Element* peFrom) = 0;
		virtual bool OnListenedPropertyChanging(Element* peFrom, const PropertyInfo* ppi, int iIndex, Value* pvOld, Value* pvNew) = 0;
		virtual void OnListenedPropertyChanged(Element* peFrom, const PropertyInfo* ppi, int iIndex, Value* pvOld, Value* pvNew) = 0;
		virtual void OnListenedInput(Element* peFrom, InputEvent* pInput) = 0;
		virtual void OnListenedEvent(Element* peFrom, Event* pEvent) = 0;
	};

    DECLARE_INTERFACE(IClassInfo)
	{
		virtual void AddRef() = 0;
		virtual int Release() = 0;
		virtual HRESULT CreateInstance(Element* pParent, DWORD* pdwDeferCookie, Element** ppElement) = 0;
		virtual const PropertyInfo* EnumPropertyInfo(UINT nEnum) = 0;
		virtual const PropertyInfo* GetByClassIndex(UINT iIndex) = 0;
		virtual UINT GetPICount() const = 0;
		virtual UINT GetGlobalIndex() const = 0;
		virtual IClassInfo* GetBaseClass() = 0;
		virtual const WCHAR* GetName() const = 0;
		virtual bool IsValidProperty(const PropertyInfo* ppi) const = 0;
		virtual bool IsSubclassOf(IClassInfo* pci) const = 0;
		virtual void Destroy() = 0;
		virtual HMODULE GetModule() const = 0;
		virtual bool IsGlobal() const = 0;
		virtual void AddChild() = 0;
		virtual void RemoveChild() = 0;
		virtual int GetChildren() const = 0;
		virtual void AssertPIZeroRef() const = 0;
	};
}

class CSafeElementListenerCB : public DirectUI::IElementListener
{
public:
	void OnListenerAttach(DirectUI::Element* peFrom) override {}
	void OnListenerDetach(DirectUI::Element* peFrom) override {}
	bool OnListenedPropertyChanging(DirectUI::Element* peFrom, const DirectUI::PropertyInfo* ppi, int iIndex, DirectUI::Value* pvOld, DirectUI::Value* pvNew) override { return true; }
	void OnListenedPropertyChanged(DirectUI::Element* peFrom, const DirectUI::PropertyInfo* ppi, int iIndex, DirectUI::Value* pvOld, DirectUI::Value* pvNew) override {}
	void OnListenedInput(DirectUI::Element* peFrom, DirectUI::InputEvent* pInput) override {}
	void OnListenedEvent(DirectUI::Element* peFrom, DirectUI::Event* pEvent) override {}
};

// world-windows-federation/dui70/DirectUI/Primitives.h
#if 1 // MODMOD: Forward declare.
namespace DirectUI
{
    class Value;
}
#endif // MODMOD
typedef DirectUI::Value* (WINAPI *DefaultValueProcT)();

enum DynamicScaleValue
{
	DSV_None = 0x0,

	DSV_Int = 0x1,

	DSV_Float = 0x1,

	DSV_Left = 0x1,
	DSV_Top = 0x2,
	DSV_Right = 0x4,
	DSV_Bottom = 0x8,

	DSV_Height = 0x1,
	DSV_Width = 0x2,

	DSV_X = 0x1,
	DSV_Y = 0x2,
};


DEFINE_ENUM_FLAG_OPERATORS(DynamicScaleValue);

namespace DirectUI
{
	// nThreadMode flags for DirectUI::InitThread
	enum THREAD_SCALING_MODE
	{
		TSM_DESKTOP = 0x1,
		TSM_IMMERSIVE = 0x2,
		TSM_PRIMARY = 0x3,
		TSM_DESKTOP_DYNAMIC = 0x4,
	};
	
	struct ScaledSIZE : SIZE
	{
		DynamicScaleValue dynamicScaleValue;
	};

	struct ScaledInt
	{
		int i;
		DynamicScaleValue dynamicScaleValue;
	};

	struct ScaledFloat
	{
		float fl;
		DynamicScaleValue dynamicScaleValue;
	};

	struct ScaledRECT : RECT
	{
		DynamicScaleValue dynamicScaleValue;
	};

	struct ScaledPOINT : POINT
	{
		DynamicScaleValue dynamicScaleValue;
	};

	struct Fill
	{
		BYTE dType;

		union
		{
			struct
			{
				COLORREF cr;
				COLORREF cr2;
				COLORREF cr3;
			} ref;

			struct
			{
				UINT uType;
				UINT uState;
			} fillDFC;

			struct
			{
				WCHAR* pszClassName;
				int iPartId;
				int iStateId;
			} fillDTB;
		};
	};

	struct Cursor
	{
		HCURSOR hCursor;
	};

	struct Graphic
	{
		HANDLE hImage;
		HANDLE hAltImage;
		USHORT cx;
		USHORT cy;

		struct
		{
			BYTE dImgType : 3;
			BYTE dMode : 4;
			bool bFlip : 1;
			bool bRTLGraphic : 1;
			bool bFreehImage : 1;
			bool bSharedResource : 1;

			union
			{
				BYTE dAlpha;

				struct
				{
					BYTE r : 8;
					BYTE g : 8;
					BYTE b : 8;
				} rgbTrans;
			};
		} BlendMode;

		HINSTANCE hResLoad;
		const WCHAR* lpszName;
		ScaledSIZE scaledSize;
		float fScaleFactor;
	};


	struct EnumMap
	{
		const WCHAR* pszEnum;
		int nEnum;
	};

	struct PropertyInfoData
	{
		Value* _pvDefault;
		int _iIndex;
		int _iGlobalIndex;
		IClassInfo* _pciOwner;
		LONG _cRef;
	};

	struct PropertyInfo
	{
		const WCHAR* pszName;
		int fFlags;
		int fGroups;
		const int* pValidValues;
		const EnumMap* pEnumMaps;
		DefaultValueProcT DefaultProc;
		PropertyInfoData* pData;
	};

	struct DepRecs
	{
		int iDepPos;
		int cDepCnt;
	};
}

// world-windows-federation/dui70/DirectUI/Value.h
namespace DirectUI
{
	enum PropertyFlags
	{
		PF_None = 0x0,
		PF_LocalOnly = 0x1,
		PF_Normal = 0x2,
		PF_TriLevel = 0x3,
		PF_Cascade = 0x4,
		PF_Inherit = 0x8,
		PF_ReadOnly = 0x10,
		PF_Cached = 0x20,
		PF_SkipNotify = 0x40,

		PF_TypeBits = 0x3,
	};

	DEFINE_ENUM_FLAG_OPERATORS(PropertyFlags);

	enum PropertyGroups
	{
		PG_None = 0x0,
		PG_AffectsDesiredSize = 0x1,
		PG_AffectsParentDesiredSize = 0x2,
		PG_AffectsLayout = 0x4,
		PG_AffectsParentLayout = 0x8,
		PG_AffectsBounds = 0x10000,
		PG_AffectsDisplay = 0x20000,
		PG_LayoutCompletion = 0x1000000,
		PG_NormalPriMask = 0xFFFF,
		PG_LowPriMask = 0xFF0000,
		PG_NotificationMask = 0xFF000000
	};

	DEFINE_ENUM_FLAG_OPERATORS(PropertyGroups);

	typedef DynamicArray<Value*> ValueList;

	class Layout;

	struct EncodedString
	{
		size_t cbBufferSize;
		WCHAR* pszEncoded;
	};

	enum class ValueType : int
	{
		Unavailable = -2,
		Unset = -1,
		Null = 0,
		Int = 1,
		Bool = 2,
		Element = 3,
		Ellist = 4,
		String = 5,
		Point = 6,
		Size = 7,
		Rect = 8,
		Color = 9,
		Layout = 10,
		Graphic = 11,
		Sheet = 12,
		Expr = 13,
		Atom = 14,
		Cursor = 15,
		Float = 18,
		DblList = 19,
	};

	class UILIB_API Value
	{
		int _dType : 6;
		int _fWeakRef : 1;
		int _cRef : 25;

		static constexpr int c_RefCountBitOffset = 7;
		static constexpr long c_SingleRefCount = 1 << c_RefCountBitOffset;
		static constexpr long c_RefCountMask = ~(c_SingleRefCount - 1);

		union
		{
			int _intVal;
			bool _boolVal;
			Element* _peVal;
			DynamicArray<Element*>* _peListVal;
			EncodedString _encodedStringVal;
			WCHAR* _pszVal;
			POINT _ptVal;
			SIZE _sizeVal;
			RECT _rectVal;
			Fill _fillVal;
			Layout* _plVal;
			Graphic* _pGraphicVal;
			StyleSheet* _ppsVal;
			Expression* _pexVal;
			ATOM _atomVal;
			Cursor _cursorVal;
			ValueList* _pvListVal;
			float _flVal;
			DynamicArray<double>* _pdblListVal;
			ScaledInt _scaledIntVal;
			ScaledFloat _scaledFloatVal;
			ScaledRECT _scaledRectVal;
			ScaledSIZE _scaledSizeVal;
			ScaledPOINT _scaledPointVal;
		};

		void _ZeroRelease();
		static HRESULT StrDupW(const WCHAR* pszIn, WCHAR** pszOut);

	public:
		static Value* WINAPI CreateInt(int dValue, DynamicScaleValue dsv = DSV_None);
		static Value* WINAPI CreateFloat(float flValue, DynamicScaleValue dsv = DSV_None);
		static Value* WINAPI CreateBool(bool bValue);
		static Value* WINAPI CreateElementRef(Element* peValue);
		static Value* WINAPI CreateElementList(DynamicArray<Element*>* peListValue);
		static Value* WINAPI CreateString(const WCHAR* pszValue, HINSTANCE hResLoad);
		static Value* WINAPI CreateEncodedString(const WCHAR* pszValue);
		static Value* WINAPI CreatePoint(int x, int y, DynamicScaleValue dsv = DSV_None);
		static Value* WINAPI CreateSize(int cx, int cy, DynamicScaleValue dsv = DSV_None);
		static Value* WINAPI CreateRect(int left, int top, int right, int bottom, DynamicScaleValue dsv = DSV_None);

		static Value* WINAPI CreateColor(COLORREF cr);
		static Value* WINAPI CreateColor(COLORREF cr0, COLORREF cr1, BYTE dType);
		static Value* WINAPI CreateColor(COLORREF cr0, COLORREF cr1, COLORREF cr2, BYTE dType);

		static Value* WINAPI CreateFill(const Fill& fill);
		static Value* WINAPI CreateDFCFill(UINT uType, UINT uState);
		static Value* WINAPI CreateDTBFill(const WCHAR* pszClassName, int iPartId, int iStateId);

		static Value* WINAPI CreateLayout(Layout* plValue);

		static Value* WINAPI CreateGraphic(ISharedBitmap* pBitmap, BYTE dBlendMode, UINT dBlendValue);
		static Value* WINAPI CreateGraphic(HBITMAP hBitmap, BYTE dBlendMode, UINT dBlendValue, bool bFlip, bool bRTL, bool bPremultiplied);
		static Value* WINAPI CreateGraphic(HICON hIcon, bool bFlip, bool bRTL, bool bShared);
		static Value* WINAPI CreateGraphic(const WCHAR* pszBMP, BYTE dBlendMode, UINT dBlendValue, USHORT cx, USHORT cy, HINSTANCE hResLoad, bool bFlip, bool bRTL);
		static Value* WINAPI CreateGraphic(const WCHAR* pszICO, USHORT cxDesired, USHORT cyDesired, HINSTANCE hResLoad, bool bFlip, bool bRTL);
		static Value* WINAPI CreateGraphic(HENHMETAFILE hEnhMetaFile, HENHMETAFILE hAltEnhMetaFile);
		static Value* WINAPI CreateGraphic(const WCHAR* pszICO, ScaledSIZE szDesired, HINSTANCE hResLoad, bool bFlip, bool bRTL);

	private:
		static Value* WINAPI CreateIconGraphicHelper(HICON hIcon, bool bFlip, bool bRTL, bool bShared);
		static HICON WINAPI ReloadIcon(Graphic* pGraphic, float fScaleFactor);

	public:
		static Value* WINAPI CreateStyleSheet(StyleSheet* ppsValue);
		static Value* WINAPI CreateExpression(Expression* pexValue);

		static Value* WINAPI CreateAtom(const WCHAR* pszValue);
		static Value* WINAPI CreateAtom(ATOM atom);

		static Value* WINAPI CreateCursor(const WCHAR* pszValue);
		static Value* WINAPI CreateCursor(HCURSOR hValue);

		static Value* WINAPI CreateValueList(ValueList* pvListValue);
		static Value* WINAPI CreateValueList(Value* pvValue);


		static Value* WINAPI CreateDoubleList(DynamicArray<double>* pdblListValue);
		static Value* WINAPI CreateDoubleList(const double* rgdbl, int cdbl);

		static Value* WINAPI CreateStringRP(const WCHAR* pszValue, HINSTANCE hResLoad);
		static Value* WINAPI CreateScaledValue(float flScaleFactor, Value* pvIn);
		static Value* WINAPI CreateElementScaledValue(Element* pe, Value* pvIn);

		void AddRef();
		void Release();
		int GetRefCount() const;

		int GetType() const;
		void* GetImage(bool bGetRTL, float fScaleFactor);

		int GetInt();

		ScaledInt* GetScaledInt();
		int GetScaledInt(float flScaleFactor);

		float GetFloat();
		bool GetBool();

		Element* GetElement();
		DynamicArray<Element*>* GetElementList();

		const WCHAR* GetString();
		HRESULT GetEncodedString(WCHAR* pszBuf, size_t cchBuf);
		size_t GetEncodedStringLength();

		const POINT* GetPoint();
		const SIZE* GetSize();
		const RECT* GetRect();
		const Fill* GetFill();

		Layout* GetLayout();
		Graphic* GetGraphic();
		StyleSheet* GetStyleSheet();
		Expression* GetExpression();
		ATOM GetAtom();
		Cursor* GetCursor();
		ValueList* GetValueList();
		DynamicArray<double>* GetDoubleList();
		WCHAR* GetStringDynamicScaling();

		int GetElementScaledInt(Element* pe);

		void GetScaledPoint(float flScaleFactor, POINT* ppt);
		void GetElementScaledPoint(Element* pe, POINT* ppt);

		void GetScaledSize(float flScaleFactor, SIZE* psize);
		void GetElementScaledSize(Element* pe, SIZE* psize);

		void GetScaledRect(float flScaleFactor, RECT* prc);
		void GetElementScaledRect(Element* pe, RECT* prc);

		float GetScaledFloat(float flScaleFactor);
		float GetElementScaledFloat(Element* pe);

		bool IsDynamicScaled();
		bool IsEqual(Value* pv);

		WCHAR* ToString(WCHAR* psz, UINT) const;
		void SetLayoutPointerToNull();

		static Value* WINAPI GetUnavailable();
		static Value* WINAPI GetNull();
		static Value* WINAPI GetUnset();
		static Value* WINAPI GetElementNull();
		static Value* WINAPI GetElListNull();
		static Value* WINAPI GetBoolTrue();
		static Value* WINAPI GetBoolFalse();
		static Value* WINAPI GetStringNull();
		static Value* WINAPI GetPointZero();
		static Value* WINAPI GetSizeZero();
		static Value* WINAPI GetRectZero();
		static Value* WINAPI GetIntZero();
		static Value* WINAPI GetIntMinusOne();
		static Value* WINAPI GetFloatZero();
		static Value* WINAPI GetFloatOne();
		static Value* WINAPI GetLayoutNull();
		static Value* WINAPI GetSheetNull();
		static Value* WINAPI GetExprNull();
		static Value* WINAPI GetAtomZero();
		static Value* WINAPI GetCursorNull();
		static Value* WINAPI GetColorTrans();
		static Value* WINAPI GetDblListEmpty();
		static Value* WINAPI GetStringRPNull();
	};

	struct _StaticValue
	{
		int _dType : 6;
		int _fWeakRef : 1;
		int _cRef : 25;
		int _val0;
		int _val1;
		int _val2;
		int _val3;
		DynamicScaleValue _dynamicScaleValue;
	};

	struct _StaticValuePtr
	{
		int _dType : 6;
		int _fWeakRef : 1;
		int _cRef : 25;
		void* _ptr;
	};

	struct _StaticValueFloat
	{
		int _dType : 6;
		int _fWeakRef : 1;
		int _cRef : 25;
		float _flVal;
		DynamicScaleValue _dynamicScaleValue;
	};

	struct _StaticValueColor
	{
		int _dType : 6;
		int _fWeakRef : 1;
		int _cRef : 25;
		BYTE dType;
		COLORREF cr;
		COLORREF cr2;
		COLORREF cr3;
	};
}

// world-windows-federation/dui70/DirectUI/Core/Element.h
typedef const DirectUI::PropertyInfo* (WINAPI *PropertyProcT)();

namespace DirectUI
{
	class StyleSheet;
	int GetPixelHelper(Element* pe, const PropertyInfo* ppi, bool fUseDefault = false);

	struct UpdateCache
	{
		bool fModified;
	};

	struct ElementIndexPair
	{
		Element* pElement;
		UINT uIndex;
	};

	class BehaviorStore;

	template <typename TKey, typename TValue>
	class BTreeLookup
	{
	};

	namespace Internal
	{
		struct ListenerData;
	}

	class DeferCycle
	{
	};

	// nActive flags
	typedef enum tagElementActiveFlags
	{
		AEF_Inactive = 0x0,
		AEF_Mouse = 0x1,
		AEF_Keyboard = 0x2,
		AEF_MouseAndKeyboard = AEF_Mouse | AEF_Keyboard,
		AEF_NoSyncFocus = 0x4,
		AEF_Pointer = 0x8,
	} ElementActiveFlags;

	// nCreate flags
	typedef enum tagElementCreateFlags
	{
		ECF_NoCreateGadget = 0x1,
		ECF_SelfLayout = 0x2,
		ECF_ReadMarkupDirection = 0x4, // TODO: Verify, HWNDElement::Initialize
		ECF_MultiTouch = 0x8, // @TODO: Verify, HWNDElement::Initialize
		ECF_PreserveAlphaChannel = 0x10, // @TODO: Verify, HWNDElement::Initialize
		ECF_MouseInputFocus = 0x20, // @TODO: Verify, HWNDElement::Initialize
		ECF_SendAllPointerEvents = 0x40, // @TODO: Verify, HWNDElement::Initialize
		ECF_DoNotStealFocus = 0x80, // @TODO: Verify, HWNDElement::Initialize
	} ElementCreateFlags;

	class DuiAccessible;

	typedef int (__cdecl *CompareCallback)(const void*, const void*);

#if 1 // MODMOD: Imported pure methods.
    Element *(__thiscall *Element_GetParent)(Element *pThis);
    HRESULT (__thiscall *Element_SetVisible)(Element *pThis, bool v);
    long (__thiscall *Element_AddListener)(Element *pThis, IElementListener *);
    void (__thiscall *Element_RemoveListener)(Element *pThis, IElementListener *);
    void (__thiscall *Element_EndDefer)(Element *pThis, DWORD dwDeferCookie);
    int (__thiscall *Element_GetIndex)(Element *pThis);
    Element* (__thiscall *Element_FindDescendent)(Element *pThis, ATOM atomId);
    HRESULT (__thiscall *Element_SetAccValue)(Element *pThis, const WCHAR* v);
#endif // MODMOD
	class UILIB_API Element
	{
	public:
		static HRESULT WINAPI Create(UINT nCreate, Element* pParent, DWORD* pdwDeferCookie, Element** ppElement);

		HRESULT Destroy(bool fDelayed = true);
		HRESULT DestroyAll(bool fDelayed);

		Element();
		Element(const Element&) = default;

		virtual ~Element();

		// ReSharper disable once CppHiddenFunction
		HRESULT Initialize(UINT nCreate, Element* peInitialParent, DWORD* pdwDeferCookie);

		Value* GetRawValue(const PropertyInfo* ppi, int iIndex, UpdateCache* puc); // TODO Check when was this added

		Value* GetValue(const PropertyInfo* ppi, int iIndex, UpdateCache* puc);
		Value* GetValue(PropertyProcT pPropertyProc, int iIndex, UpdateCache* puc);

		HRESULT SetValue(const PropertyInfo* ppi, int iIndex, Value* pv);
		HRESULT SetValue(PropertyProcT pPropertyProc, int iIndex, Value* pv);

		HRESULT RemoveLocalValue(const PropertyInfo* ppi);
		HRESULT RemoveLocalValue(PropertyProcT pPropertyProc);

		void StartDefer(DWORD* pdwDeferCookie);
		void EndDefer(DWORD dwDeferCookie)
        {   // MODMOD: Call pure method implementation.
            return Element_EndDefer(this, dwDeferCookie);
        }
		void UpdateLayout();

		DeferCycle* GetDeferObject();
		DeferCycle* TestDeferObject();

		bool IsValidAccessor(const PropertyInfo* ppi, int iIndex, bool bSetting);
		static bool IsValidValue(const PropertyInfo* ppi, Value* pv);

		bool IsRTL();
#if 0  // MODMOD: This was causing alignment issues in the vtable for some
       // reason that I don't fully understand, so I commented it out.
		virtual bool IsRTLReading();
#endif // MODMOD
		virtual bool IsContentProtected();
		virtual const WCHAR* GetContentStringAsDisplayed(Value** ppv);
		const WCHAR* GetAccNameAsDisplayed(Value** ppv);

		virtual bool OnPropertyChanging(PropertyInfo* ppi, int iIndex, Value* pvOld, Value* pvNew);
		virtual bool OnPropertyChanging(const PropertyInfo* ppi, int iIndex, Value* pvOld, Value* pvNew);
		virtual void OnPropertyChanged(PropertyInfo* ppi, int iIndex, Value* pvOld, Value* pvNew);
		virtual void OnPropertyChanged(const PropertyInfo* ppi, int iIndex, Value* pvOld, Value* pvNew);

		virtual void OnGroupChanged(int fGroups, bool bLowPri);
		virtual void OnInput(InputEvent* pInput);
		virtual void OnKeyFocusMoved(Element* peFrom, Element* peTo);
		virtual void OnMouseFocusMoved(Element* peFrom, Element* peTo);
		virtual void OnDestroy();

		void FireEvent(Event* pEvent, bool fFull, bool fUseSpecifiedTarget);
		void BroadcastEvent(Event* pEvent);
		virtual void OnEvent(Event* pEvent);

		virtual void Paint(HDC hDC, const RECT* prcBounds, const RECT* prcInvalid, RECT* prcSkipBorder, RECT* prcSkipContent);
		void PaintContent(HDC hDC, const RECT* prcContent);
		void PaintStringContent(HDC hDC, const RECT* prcContent, Value* pvContent, int dCAlign);
		void PaintFocusRect(HDC hDC, const RECT* prcBounds, const RECT* prcContent);
		void PaintBorder(HDC hDC, Value* pvBackgnd, RECT* prcPaint, const RECT& rcBorder);
		void PaintBackground(HDC hDC, Value* pvBackgnd, const RECT& rcBounds, const RECT& rcInvalid, const RECT& rcPadding, const RECT& rcBorder);
		void PaintEdgeHighlight(HDC hDC, const RECT& rcPaint, const RECT& rcInvalid); // TODO Check when was this added

		virtual SIZE GetContentSize(int dConstW, int dConstH, Surface* psrf);

		float GetTreeAlphaLevel();

		HRESULT Add(Element* pe);
		virtual HRESULT Add(Element** ppe, UINT cCount);
		HRESULT Add(Element* pe, CompareCallback lpfnCompare); // TODO Check when was this added

		HRESULT Insert(Element* pe, UINT iInsertIdx);
		virtual HRESULT Insert(Element** ppe, UINT cCount, UINT iInsertIdx);

		HRESULT SortChildren(CompareCallback lpfnCompare);
		HRESULT ShiftChild(UINT iOldIndex, UINT iNewIndex); // TODO Check when was this added

		HRESULT Remove(Element* pe);
		virtual HRESULT Remove(Element** ppe, UINT cCount);
		HRESULT RemoveAll();

		Element* FindDescendent(ATOM atomID)
        {   // MODMOD: Call pure method implementation.
            return Element_FindDescendent(this, atomID);
        }
		void MapElementPoint(Element* peFrom, const POINT* pptFrom, POINT* pptTo);
		Element* GetImmediateChild(Element* peFrom);
		bool IsDescendent(Element* pe);
		virtual Element* GetAdjacent(Element* peFrom, int iNavDir, const NavReference* pnr, DWORD dwFlags);
		Element* GetKeyWithinChild();
		Element* GetMouseWithinChild();

		bool EnsureVisible();
		bool EnsureVisible(UINT uChild);
		virtual bool EnsureVisible(int x, int y, int cx, int cy);

		virtual void SetKeyFocus();

		HRESULT AddListener(IElementListener* pel)
        {   // MODMOD: Call pure method implementation.
            return Element_AddListener(this, pel);
        }

		void RemoveListener(IElementListener* pel)
        {   // MODMOD: Call pure method implementation.
            return Element_RemoveListener(this, pel);
        }

		virtual HRESULT AddBehavior(IDuiBehavior* pBehavior);
		virtual HRESULT RemoveBehavior(IDuiBehavior* pBehavior);

		void InvokeAnimation(int dAni, UINT nTypeMask);
		void InvokeAnimation(UINT nTypes, UINT nInterpol, float flDuration, float flDelay, bool fPushToChildren);
		void StopAnimation(UINT nTypes);

		virtual UINT MessageCallback(GMSG* pgMsg);

		SIZE _UpdateDesiredSize(int cxConstraint, int cyConstraint, Surface* psrf);
		void _UpdateLayoutPosition(int dX, int dY);
		void _UpdateLayoutSize(int dWidth, int dHeight);
		void _StartOptimizedLayoutQ();
		void _EndOptimizedLayoutQ();
		UINT _GetNeedsLayout();
		static bool _SetGroupChanges(Element* pe, int fGroups, DeferCycle* pdc);
		static void _TransferGroupFlags(Element* pe, int fGroups);
		int _SetNeedsLayout(UINT fNeedsLayout);
		static int _MarkElementForLayout(Element* pe, UINT fNeedsLayout);
		static int _MarkElementForDS(Element* pe);
		void _ClearNeedsLayout();
		static void _AddDependency(Element* pe, const PropertyInfo* ppi, int iIndex, DepRecs* pdr, DeferCycle* pdc, HRESULT* phr);
		static HRESULT _DisplayNodeCallback(HGADGET hgadCur, void* pvCur, EventMsg* pGMsg);

		virtual STDMETHODIMP QueryInterface(REFIID riid, void** ppvObject);
		STDMETHODIMP_(ULONG) AddRef(); // @Note: Not virtual
		STDMETHODIMP_(ULONG) Release(); // @Note: Not virtual

		int _GetChangesUpdatePass();
		void Detach(DeferCycle* pdc);
		bool UiaEvents();
		void EnableUiaEvents(bool fEnable);
		bool GetClickablePoint(POINT* ptClick);
		virtual void GetImmersiveFocusRectOffsets(RECT* prc);

		template <typename T>
		void PostEvent(T* pEvent) { _PostEvent(pEvent, 0x83F8); }

	private:
		Element* FindDescendentWorker(ATOM atomID);
		void _GetBuriedSheetDependencies(const PropertyInfo* ppi, Element* peNewParent, DepRecs* pdr, DeferCycle* pdc, HRESULT* phr);
		HRESULT _GetDependencies(const PropertyInfo* ppi, int iIndex, DepRecs* pdr, int iPCSrcRoot, Value* pvNewRoot, DeferCycle* pdc);
		static void _VoidPCNotifyTree(int iPCPos, DeferCycle* pdc);
		int _CachedValueIsEqual(const PropertyInfo* ppi, Element* peParent);
		Value* _GetLocalValueFromVM(const PropertyInfo* ppi);
		Value* _GetLocalValue(const PropertyInfo* ppi);
		Value* _GetSpecifiedValueIgnoreCache(const PropertyInfo* ppi);
		Value* _GetSpecifiedValue(const PropertyInfo* ppi, UpdateCache* puc);
		Value* _GetComputedValue(const PropertyInfo* ppi, UpdateCache* puc);
		void _UpdatePropertyInCache(const PropertyInfo* ppi);
		void _InheritProperties();
		void _FlushDS(DeferCycle*);
		HRESULT _PreSourceChange(PropertyProcT proc, int iIndex, Value* pvOld, Value* pvNew);
		HRESULT _PreSourceChange(const PropertyInfo* ppi, int iIndex, Value* pvOld, Value* pvNew);
		HRESULT _PostSourceChange();
		void _BroadcastEventWorker(Event* pEvent);
		void _PostEvent(Event* pEvent, int nMsg); // TODO Check when was this added
		static bool CALLBACK s_HandleDUIEventMessage(Element* pe, EventMsg* pEventMsg); // TODO Check when was this added
		UINT GetCommonDrawTextFlags(int dCAlign);
		WCHAR* RemoveShortcutFromName(const WCHAR* pszName);
		void _SyncVisible();
		void _SyncBackground();
		void _SyncRedrawStyle();
		bool IsPointValid(double x, double y);
		bool TryLinePattern(POINT* pt, const RECT& rcParent);
		bool TryPattern(double x, double y, POINT* pt, const RECT& rcParent);
		bool TrySparsePattern(POINT* pt, const RECT& rcParent);
		HRESULT _SetRelPixValue(const PropertyInfo* ppi, int nValue); // TODO Check when was this added
		HRESULT _SetRelPixRect(const PropertyInfo* ppi, int l, int t, int r, int b); // TODO Check when was this added
		HRESULT GetTheme(const WCHAR* pszClass, HTHEME* phTheme); // TODO Check when was this added

	protected:
		static void _FlushLayout(Element* pe, DeferCycle* pdc);
		static void _InvalidateCachedDSConstraints(Element* pe);
		virtual void _SelfLayoutDoLayout(int cx, int cy);
		virtual SIZE _SelfLayoutUpdateDesiredSize(int dConstW, int dConstH, Surface* psrf);
		HRESULT _SetValue(const PropertyInfo* ppi, int iIndex, Value* pv, bool fInternalCall);
		HRESULT _SetValue(PropertyProcT pPropertyProc, int iIndex, Value* pv, bool fInternalCall);
		HRESULT _RemoveLocalValue(const PropertyInfo* ppi, bool fInternalCall);
		HRESULT _RemoveLocalValue(PropertyProcT pPropertyProc, bool fInternalCall);
		virtual void OnHosted(Element* peNewRoot);
		virtual void OnUnHosted(Element* peOldRoot);
		void MarkHosted();
		void MarkSelfLayout();
		virtual void UpdateTooltip(Element* pe);
		virtual void ActivateTooltip(Element* pe, DWORD dwFlags);
		virtual void RemoveTooltip(Element* pe);
		void _OnFontPropChanged(Value* pvFont);

	public:
		void MarkNeedsDSUpdate();
		bool NeedsDSUpdate();
		void DoubleBuffered(bool fEnabled);
		int IsRoot();
		Element* GetRoot();
		Element* GetTopLevel();
		HRESULT GetRootRelativeBounds(RECT* prc);

		static RTL_CRITICAL_SECTION* GetFactoryLock();

		static UID WINAPI KeyboardNavigate();
		static UID WINAPI AnimationChange();
		static UID WINAPI DCompDeviceRebuilt(); // TODO Check when was this added

		static const PropertyInfo* WINAPI ParentProp();
		static const PropertyInfo* WINAPI ChildrenProp();
		static const PropertyInfo* WINAPI VisibleProp();
		static const PropertyInfo* WINAPI WidthProp();
		static const PropertyInfo* WINAPI HeightProp();
		static const PropertyInfo* WINAPI LocationProp();
		static const PropertyInfo* WINAPI ExtentProp();
		static const PropertyInfo* WINAPI XProp();
		static const PropertyInfo* WINAPI YProp();
		static const PropertyInfo* WINAPI PosInLayoutProp();
		static const PropertyInfo* WINAPI SizeInLayoutProp();
		static const PropertyInfo* WINAPI DesiredSizeProp();
		static const PropertyInfo* WINAPI LastDSConstProp();
		static const PropertyInfo* WINAPI LayoutProp();
		static const PropertyInfo* WINAPI LayoutPosProp();
		static const PropertyInfo* WINAPI BorderThicknessProp();
		static const PropertyInfo* WINAPI BorderStyleProp();
		static const PropertyInfo* WINAPI BorderColorProp();
		static const PropertyInfo* WINAPI PaddingProp();
		static const PropertyInfo* WINAPI MarginProp();
		static const PropertyInfo* WINAPI ForegroundProp();
		static const PropertyInfo* WINAPI BackgroundProp();
		static const PropertyInfo* WINAPI ContentProp();
		static const PropertyInfo* WINAPI FontFaceProp();
		static const PropertyInfo* WINAPI FontSizeProp();
		static const PropertyInfo* WINAPI FontWeightProp();
		static const PropertyInfo* WINAPI FontStyleProp();
		static const PropertyInfo* WINAPI FontQualityProp();
		static const PropertyInfo* WINAPI ActiveProp();
		static const PropertyInfo* WINAPI ContentAlignProp();
		static const PropertyInfo* WINAPI KeyFocusedProp();
		static const PropertyInfo* WINAPI KeyWithinProp();
		static const PropertyInfo* WINAPI MouseFocusedProp();
		static const PropertyInfo* WINAPI MouseWithinProp();
		static const PropertyInfo* WINAPI ClassProp();
		static const PropertyInfo* WINAPI IDProp();
		static const PropertyInfo* WINAPI SheetProp();
		static const PropertyInfo* WINAPI SelectedProp();
		static const PropertyInfo* WINAPI AlphaProp();
		static const PropertyInfo* WINAPI AnimationProp();
		static const PropertyInfo* WINAPI CursorProp();
		static const PropertyInfo* WINAPI DirectionProp();
		static const PropertyInfo* WINAPI AccessibleProp();
		static const PropertyInfo* WINAPI AccRoleProp();
		static const PropertyInfo* WINAPI AccStateProp();
		static const PropertyInfo* WINAPI AccNameProp();
		static const PropertyInfo* WINAPI AccDescProp();
		static const PropertyInfo* WINAPI AccValueProp();
		static const PropertyInfo* WINAPI AccDefActionProp();
		static const PropertyInfo* WINAPI AccHelpProp();
		static const PropertyInfo* WINAPI AccItemTypeProp();
		static const PropertyInfo* WINAPI AccItemStatusProp();
		static const PropertyInfo* WINAPI ShortcutProp();
		static const PropertyInfo* WINAPI EnabledProp();
		static const PropertyInfo* WINAPI MinSizeProp();
		static const PropertyInfo* WINAPI OverhangProp();
		static const PropertyInfo* WINAPI TooltipProp();
		static const PropertyInfo* WINAPI TooltipMaxWidthProp();
		static const PropertyInfo* WINAPI FontProp();
		static const PropertyInfo* WINAPI WindowActiveProp();
		static const PropertyInfo* WINAPI AbsorbsShortcutProp();
		static const PropertyInfo* WINAPI CompositedTextProp();
		static const PropertyInfo* WINAPI TextGlowSizeProp();
		static const PropertyInfo* WINAPI HighDPIProp();
		static const PropertyInfo* WINAPI DPIProp();
		static const PropertyInfo* WINAPI CustomProp();
		static const PropertyInfo* WINAPI ShadowIntensityProp();
		static const PropertyInfo* WINAPI EdgeHighlightThicknessProp(); // TODO Check when was this added
		static const PropertyInfo* WINAPI EdgeHighlightColorProp(); // TODO Check when was this added
		static const PropertyInfo* WINAPI ScaleFactorProp(); // TODO Check when was this added
		static const PropertyInfo* WINAPI UsesDesktopPerMonitorScalingProp(); // TODO Check when was this added

	protected:
		HGADGET _hgDisplayNode;
		BehaviorStore* _pBehaviorStore;

	private:
		int _iIndex;
		BTreeLookup<const PropertyInfo*, Value*>* _pvmLocal;
		int _iGCSlot;
		int _iGCLPSlot;
		int _iPCTail;
		DeferCycle* _pDeferCycle;
		Internal::ListenerData* _pld;
		Element* _peInitialParent;
		Element* _peLocParent;
		POINT _ptLocPosInLayt;
		SIZE _sizeLocSizeInLayt;
		SIZE _sizeLocLastDSConst;
		SIZE _sizeLocDesiredSize;
		int _dSpecLayoutPos;
		Value* _pvSpecSheet;
		int _dSpecAlpha;
		int _dPVLAnimationState;
		ATOM _atomSpecID;

		struct _BitMap
		{
			bool bLocKeyWithin : 1;
			bool bLocMouseWithin : 1;
			bool bCmpVisible : 1;
			bool bSpecVisible : 1;
			bool bSpecSelected : 1;
			bool bSpecKeyFocused : 1;
			bool bSpecMouseFocused : 1;
			bool bSpecAccessible : 1;
			bool bSpecEnabled : 1;
			bool bHasChildren : 1;
			bool bHasLayout : 1;
			bool bHasBorder : 1;
			bool bHasPadding : 1;
			bool bHasMargin : 1;
			bool bHasContent : 1;
			bool bDefaultCAlign : 1;
			bool bWordWrap : 1;
			bool bHasAnimation : 1;
			bool bDefaultCursor : 1;
			bool bDefaultBorderColor : 1;
			bool bDefaultForeground : 1;
			bool bDefaultFontWeight : 1;
			bool bDefaultFontStyle : 1;
			bool bDefaultFontQuality : 1;
			bool bSelfLayout : 1;
			bool bNeedsDSUpdate : 1;
			bool bDestroyed : 1;
			bool bHosted : 1;
			bool bHasTooltip : 1;
			bool bCompositedText : 1;
			bool bUiaEvents : 1;
			bool bPreserveAlphaChannel : 1;
			UINT fNeedsLayout : 2;
			UINT fSpecActive : 4;
			UINT nSpecDirection : 1;
			UINT nUseDefaultFontSize : 1;
			UINT bHasEdgeHighlight : 1;
			UINT nGetsLayoutCompleteGC : 1;
			UINT fFontSizeInRP : 1;
			UINT nScaleFactor : 10;
			UINT bUsesDesktopPerMonitorScaling : 1;
		};

		_BitMap _fBit;
		int _dSpecFontSize;
		Value* _pvSpecFontFace;
		Value* _pvSpecBackground;

	public:
		DuiAccessible* _pDuiAccessible;

		HGADGET GetDisplayNode();
		int GetIndex()
        {   // MODMOD: Call pure method implementation.
            return Element_GetIndex(this);
        }
		bool IsDestroyed();
		bool IsHosted();
		bool IsSelfLayout();
		bool IsBehaviorLayout() const; // TODO Check when was this added
		bool HasChildren();
		bool HasLayout();
		bool HasBorder();
		bool HasPadding();
		bool HasMargin();
		bool HasContent();
		bool IsDefaultCAlign();
		bool IsWordWrap();
		bool HasAnimation();
		bool IsDefaultCursor();
		bool HasEdgeHighlight(); // TODO Check when was this added
		bool HasPVLAnimationState(UINT dState); // TODO Check when was this added
		void GetRenderBorderThickness(RECT* prc); // TODO Check when was this added
		void GetRenderPadding(RECT* prc); // TODO Check when was this added
		void GetRenderMargin(RECT* prc); // TODO Check when was this added
		void GetRenderEdgeHighlightThickness(RECT* prc); // TODO Check when was this added
		void GetRenderMinSize(SIZE* prc); // TODO Check when was this added
		Element* GetParent() { return Element_GetParent(this); }
		bool GetVisible();
		int GetWidth();
		int GetHeight();
		DynamicArray<Element*>* GetChildren(Value** ppv);
		int GetX();
		int GetY();
		Layout* GetLayout(Value** ppv);
		int GetLayoutPos();
		const RECT* GetBorderThickness(Value** ppv);
		int GetBorderStyle();
		int GetBorderStdColor();
		const Fill* GetBorderColor(Value** ppv);
		const RECT* GetPadding(Value** ppv);
		const RECT* GetMargin(Value** ppv);
		const POINT* GetLocation(Value** ppv);
		const SIZE* GetExtent(Value** ppv);
		const SIZE* GetDesiredSize();
		int GetForegroundStdColor();
		const Fill* GetForegroundColor(Value** ppv);
		int GetBackgroundStdColor();
		const Fill* GetBackgroundColor(Value** ppv);
		const RECT* GetEdgeHighlightThickness(Value** ppv); // TODO Check when was this added
		const Fill* GetEdgeHighlightColor(Value** ppv); // TODO Check when was this added
		float GetElementScaleFactor(); // TODO Check when was this added
		const WCHAR* GetContentString(Value** ppv);
		HRESULT GetEncodedContentString(WCHAR*, size_t cchString);
		size_t GetEncodedContentStringLength(); // TODO Check when was this added
		const WCHAR* GetFontFace(Value** ppv);
		int GetFontSize();
		int GetFontWeight();
		int GetFontStyle();
		int GetFontQuality();
		bool IsCompositedText();
		int GetTextGlowSize();
		int GetActive();
		int GetContentAlign();
		virtual bool GetKeyFocused();
		bool GetKeyWithin();
		bool GetMouseFocused();
		bool GetMouseWithin();
		const WCHAR* GetClass(Value** ppv);
		ATOM GetID();
		StyleSheet* GetSheet();
		bool GetSelected();
		int GetAlpha();
		bool GetPreserveAlphaChannel() const; // TODO Check when was this added
		void SetPreserveAlphaChannel(bool fPreserveAlpha); // TODO Check when was this added
		int GetAnimation();
		int GetPVLAnimationState(); // TODO Check when was this added
		int GetDirection();
		bool GetAccessible();
		int GetAccRole();
		int GetAccState();
		const WCHAR* GetAccName(Value** ppv);
		const WCHAR* GetAccDesc(Value** ppv);
		const WCHAR* GetAccValue(Value** ppv);
		const WCHAR* GetAccDefAction(Value** ppv);
		const WCHAR* GetAccHelp(Value** ppv);
		const WCHAR* GetAccItemType(Value** ppv);
		const WCHAR* GetAccItemStatus(Value** ppv);
		int GetShortcut();
		bool GetEnabled();
		const SIZE* GetMinSize(Value** ppv);
		bool GetOverhang();
		bool GetTooltip();
		int GetTooltipMaxWidth();
		const WCHAR* GetFont(Value** ppv);
		int GetColorize();
		bool GetWindowActive();
		bool GetAbsorbsShortcut();
		bool GetHighDPI();
		int GetDPI();
		int GetShadowIntensity();

		void SetLayoutCompletionNotify(bool v); // TODO Check when was this added
		void SetPVLAnimationState(int v); // TODO Check when was this added
		HRESULT SetVisible(bool v)
        {   // MODMOD: Call pure method implementation.
            return Element_SetVisible(this, v);
        }
		HRESULT SetWidth(int v);
		HRESULT SetHeight(int v);
		HRESULT SetRelPixWidth(int v); // TODO Check when was this added
		HRESULT SetRelPixHeight(int v); // TODO Check when was this added
		HRESULT SetX(int v);
		HRESULT SetY(int v);
		HRESULT SetLayout(Layout* v);
		HRESULT SetLayoutPos(int v);
		HRESULT SetBorderThickness(int l, int t, int r, int b);
		HRESULT SetBorderStyle(int v);
		HRESULT SetBorderStdColor(int v);
		HRESULT SetBorderColor(COLORREF cr);
		HRESULT SetBorderGradientColor(COLORREF cr0, COLORREF cr1, BYTE dType);
		HRESULT SetPadding(int l, int t, int r, int b);
		HRESULT SetRelPixPadding(int l, int t, int r, int b); // TODO Check when was this added
		HRESULT SetMargin(int l, int t, int r, int b);
		HRESULT SetRelPixMargin(int l, int t, int r, int b); // TODO Check when was this added
		HRESULT SetForegroundStdColor(int v);
		HRESULT SetForegroundColor(COLORREF cr);
		HRESULT SetForegroundColor(COLORREF cr0, COLORREF cr1, BYTE dType);
		HRESULT SetForegroundColor(COLORREF cr0, COLORREF cr1, COLORREF cr2, BYTE dType);
		HRESULT SetBackgroundStdColor(int v);
		HRESULT SetBackgroundColor(const Fill& fill);
		HRESULT SetBackgroundColor(const WCHAR* pszClassName, int iPartId, int iStateId);
		HRESULT SetBackgroundColor(COLORREF cr);
		HRESULT SetBackgroundColor(COLORREF cr0, COLORREF cr1, BYTE dType);
		HRESULT SetBackgroundColor(COLORREF cr0, COLORREF cr1, COLORREF cr2, BYTE dType);
		HRESULT SetContentString(const WCHAR* v);
		HRESULT SetEncodedContentString(const WCHAR* v);
		HRESULT SetContentGraphic(const WCHAR* v, BYTE dBlendMode, UINT dBlendValue);
		HRESULT SetContentGraphic(const WCHAR* v, WORD cxDesired, WORD cyDesired);
		HRESULT SetFontFace(const WCHAR* v);
		HRESULT SetFontSize(int v);
		HRESULT SetFontWeight(int v);
		HRESULT SetFontStyle(int v);
		HRESULT SetFontQuality(int v);
		HRESULT SetActive(int v);
		HRESULT SetCompositedText(bool v);
		HRESULT SetTextGlowSize(int v);
		HRESULT SetContentAlign(int v);
		HRESULT SetClass(const WCHAR* v);
		HRESULT SetID(const WCHAR* v);
		HRESULT SetSheet(StyleSheet* v);
		HRESULT SetSelected(bool v);
		HRESULT SetAlpha(int v);
		HRESULT SetAnimation(int v);
		HRESULT SetStdCursor(int v);
		HRESULT SetCursor(const WCHAR* v);
		HRESULT SetCursorHandle(HCURSOR hCursor);
		HRESULT SetDirection(int v);
		HRESULT SetAccessible(bool v);
		HRESULT SetAccRole(int v);
		HRESULT SetAccState(int v);
		HRESULT SetAccName(const WCHAR* v);
		HRESULT SetAccDesc(const WCHAR* v);
		HRESULT SetAccValue(const WCHAR* v)
        {   // MODMOD: Call pure method implementation.
            return Element_SetAccValue(this, v);
        }
		HRESULT SetAccDefAction(const WCHAR* v);
		HRESULT SetAccHelp(const WCHAR* v);
		HRESULT SetAccItemType(const WCHAR* v);
		HRESULT SetAccItemStatus(const WCHAR* v);
		HRESULT SetShortcut(int v);
		HRESULT SetEnabled(bool v);
		HRESULT SetMinSize(int cx, int cy);
		HRESULT SetOverhang(bool v);
		HRESULT SetTooltip(bool v);
		HRESULT SetTooltipMaxWidth(int v);
		HRESULT SetFont(const WCHAR* v);
		HRESULT SetWindowActive(bool v);
		HRESULT SetAbsorbsShortcut(bool v);
		HRESULT SetEdgeHighlightThickness(int l, int t, int r, int b); // TODO Check when was this added
		HRESULT SetEdgeHighlightColor(COLORREF cr); // TODO Check when was this added
		// ReSharper disable once CppHiddenFunction
		WCHAR GetShortcutChar();
		HRESULT SetShadowIntensity(int v);

		static IClassInfo* WINAPI GetClassInfoPtr();
		static void WINAPI SetClassInfoPtr(IClassInfo* pClass);

	private:
		static IClassInfo* s_pClassInfo;

	public:
		virtual IClassInfo* GetClassInfoW();

		static HRESULT WINAPI Register();
		static HRESULT WINAPI UnRegister(IClassInfo** ppClassInfo);
		virtual HRESULT GetAccessibleImpl(IAccessible** ppAccessible);
		HRESULT QueueDefaultAction();
		virtual HRESULT DefaultAction();
		virtual HRESULT GetUIAElementProvider(REFIID riid, void** ppv);
		virtual HRESULT GetElementProviderImpl(InvokeHelper* pih, ElementProvider** ppprv);
		virtual void HandleUiaDestroyListener();
		virtual void HandleUiaPropertyListener(const PropertyInfo* ppi, int iIndex, Value* pvOld, Value* pvNew);
		virtual void HandleUiaPropertyChangingListener(const PropertyInfo* ppi);
		virtual void HandleUiaEventListener(Event* pEvent);
		virtual Element* GetUiaFocusDelegate();

		void SetOverrideScaleFactor(float flscale); // TODO Check when was this added

	protected:
		void _Fill(HDC hDC, DWORD crFill, int left, int top, int right, int bottom, bool fForceOpaque); // TODO Check when was this added

	private:
		class Impl
		{
		};

		Impl* _pImpl;
		HWND _rootWindowForTheming;

		friend class __Element_Check;
	};

	typedef const WCHAR* (Element::*PfnStringVal)(Value**);

#if 0 // This mod does not need accessibility.
	class UILIB_API DECLSPEC_NOVTABLE ElementProxy : public ProviderProxy
	{
	public:
		static ElementProxy* WINAPI Create(Element* pe);

		HRESULT DoMethod(MethodId methodId, va_list args) override;

		ElementProxy(const ElementProxy&) = default;

	protected:
		ElementProxy();

		void Init(Element* pe) override;

		HRESULT Navigate(NavigateDirection direction, IRawElementProviderFragment** ppprv);
		HRESULT GetBoundingRect(UiaRect* prect);
		HRESULT GetProperty(VARIANT* pvar, PROPERTYID propertyId);
		HRESULT GetRuntimeId(SAFEARRAY** ppArray);
		HRESULT SetString(VARIANT* pvar, PfnStringVal pfn);
		HRESULT GetFragmentRoot(IRawElementProviderFragmentRoot** ppprv);
		HRESULT IsPatternSupported(Schema::Pattern pattern, bool* pf);
		HRESULT GetLabel(VARIANT* pvar);
		HRESULT GetContent(VARIANT* pvar, IAccessible* pAccessible);
		HRESULT GetProviderOptions(ProviderOptions* ppo);
		HRESULT GetHwnd(HWND* phwnd);
		HRESULT GetAutomationId(VARIANT* pvar);
		void GetControlType(VARIANT* pvar, IAccessible* pAccessible);
		BOOL _UsesUIAProxies();

	private:
		bool _IsSemanticZoomControl(int id);
		bool _IsWindowHostUsingDoNotStealFocusFlag();
	};
#endif

	enum MethodIdTag
	{
		MethodId_Element_GetHWND = 0,
		MethodId_Element_ElementFromPoint = 1,
		MethodId_Element_GetFocus = 2,
		MethodId_Element_AdviseEventAdded = 3,
		MethodId_Element_AdviseEventRemoved = 4,
		MethodId_Element_SetFocus = 5,
		MethodId_Element_GetRoot = 6,
		MethodId_Element_Navigate = 7,
		MethodId_Element_GetBoundingRect = 8,
		MethodId_Element_GetProperty = 9,
		MethodId_Element_IsPatternSupported = 10,
		MethodId_Element_GetRuntimeId = 11,
		MethodId_Element_GetProviderOptions = 12,
		MethodId_Drag_GetIsGrabbed = 13,
		MethodId_Drag_GetDropEffect = 14,
		MethodId_Drag_GetDropEffects = 15,
		MethodId_Drag_GetGrabbedItems = 16,
		MethodId_ExpandCollapse_Expand = 17,
		MethodId_ExpandCollapse_Collapse = 18,
		MethodId_ExpandCollapse_GetExpandCollapseState = 19,
		MethodId_Grid_GetItem = 20,
		MethodId_Grid_GetRowCount = 21,
		MethodId_Grid_GetColumnCount = 22,
		MethodId_GridItem_GetRow = 23,
		MethodId_GridItem_GetColumn = 24,
		MethodId_GridItem_GetContainingGrid = 25,
		MethodId_Invoke_Invoke = 26,
		MethodId_RangeValue_SetValue = 27,
		MethodId_RangeValue_GetValue = 28,
		MethodId_RangeValue_GetIsReadOnly = 29,
		MethodId_RangeValue_GetMaximum = 30,
		MethodId_RangeValue_GetMinimum = 31,
		MethodId_RangeValue_GetLargeChange = 32,
		MethodId_RangeValue_GetSmallChange = 33,
		MethodId_Scroll_Scroll = 34,
		MethodId_Scroll_SetScrollPercent = 35,
		MethodId_Scroll_GetHorizontalScrollPercent = 36,
		MethodId_Scroll_GetVerticalScrollPercent = 37,
		MethodId_Scroll_GetHorizontalViewSize = 38,
		MethodId_Scroll_GetVerticalViewSize = 39,
		MethodId_Scroll_GetHorizontallyScrollable = 40,
		MethodId_Scroll_GetVerticallyScrollable = 41,
		MethodId_ScrollItem_ScrollIntoView = 42,
		MethodId_SelectionItem_Select = 43,
		MethodId_SelectionItem_GetIsSelected = 44,
		MethodId_SelectionItem_GetSelectionContainer = 45,
		MethodId_SelectionItem_AddToSelection = 46,
		MethodId_SelectionItem_RemoveFromSelection = 47,
		MethodId_Selection_GetIsSelectionRequired = 48,
		MethodId_Selection_GetSelection = 49,
		MethodId_Table_GetColumnHeaders = 50,
		MethodId_TableItem_GetColumnHeaders = 51,
		MethodId_Toggle_Toggle = 52,
		MethodId_Toggle_GetToggleState = 53,
		MethodId_Value_SetValue = 54,
		MethodId_Value_GetValue = 55,
		MethodId_Value_GetIsReadOnly = 56,
		MethodId_Window_SetVisualState = 57,
		MethodId_Window_Close = 58,
		MethodId_Window_WaitForInputIdle = 59,
		MethodId_Window_GetCanMaximize = 60,
		MethodId_Window_GetCanMinimize = 61,
		MethodId_Window_GetIsModal = 62,
		MethodId_Window_GetWindowVisualState = 63,
		MethodId_Window_GetWindowInteractionState = 64,
		MethodId_Window_GetIsTopmost = 65,
		MethodId_Count = 66,
	};

	class AutoDefer
	{
		AutoDefer(const AutoDefer&) = delete;

	public:
		AutoDefer(Element* pElement)
			: AutoDefer(pElement, 0)
		{
		}

		AutoDefer(Element* pElement, DWORD dwCookie)
			: _pElement(pElement), _dwCookie(dwCookie)
		{
			pElement->StartDefer(&_dwCookie);
		}

		~AutoDefer()
		{
			EndDefer();
		}

		void EndDefer()
		{
			if (_dwCookie)
			{
				_pElement->EndDefer(_dwCookie);
				_dwCookie = 0;
			}
		}

	private:
		Element* _pElement;
		DWORD _dwCookie;
	};

#if 0 // Incomplete type causes issues, and this is not necessary.
	struct UpdateContentSizeEvent : Event
	{
		int nContentSizeFlags;
		SIZE sizeContentOverride;
		POINT positionContentOverride;
	};
#endif    
}

// world-windows-foundation/dui70/DirectUI/ClassInfo.h
// MODMOD: Only took what's necessary.

template <typename T>
BOOL IsSubclassOf(DirectUI::Element* pe)
{
    RUNTIME_ASSERT(pe != nullptr, "Element must be set.");
	return pe->GetClassInfoW()->IsSubclassOf(((T*)pe)->T::GetClassInfoW()); // @Note: bool -> BOOL, no != 0
}

template <typename T>
T* element_cast(DirectUI::Element* pe)
{
	T* p = nullptr;
	if (pe && IsSubclassOf<T>(pe))
	{
		p = (T*)pe;
	}
	return p;
}

template <typename T>
HRESULT ElementCast(DirectUI::Element* pe, T** ppT)
{
	*ppT = element_cast<T>(pe);
	return *ppT ? S_OK : E_FAIL;
}

template <typename T>
T* element_interface_cast(DirectUI::Element* pe)
{
	T* p = nullptr;
	return pe && SUCCEEDED(pe->QueryInterface(__uuidof(*p), (void**)&p)) ? p : nullptr;
}

template <typename T>
BOOL IsClassOf(DirectUI::Element* pe)
{
	return pe->GetClassInfoW() == ((T*)pe)->T::GetClassInfoW();
}

#undef DUI_GET_CLASS_INFO
#undef DUI_SET_CLASS_INFO

// world-windows-federation/dui70/DirectUI/Control/ElementWithHWND.h
namespace DirectUI { class ElementWithHWND; }
DirectUI::IClassInfo *(*__pfnGetClassInfoW)(DirectUI::ElementWithHWND *pThis);
namespace DirectUI
{
	class UILIB_API ElementWithHWND : public Element
	{
	public:
		static HRESULT WINAPI Create(Element* pParent, DWORD* pdwDeferCookie, Element** ppElement);

		virtual HWND GetHWND() = 0;

		static IClassInfo* WINAPI GetClassInfoPtr();
		static void WINAPI SetClassInfoPtr(IClassInfo* pClass);

	private:
		static IClassInfo* s_pClassInfo;

	public:
        //static IClassInfo *(*__pfnGetClassInfoW)(ElementWithHWND *pThis);
		IClassInfo* GetClassInfoW() override { return __pfnGetClassInfoW(this); }

		static HRESULT WINAPI Register();
	};
}

// world-windows-federation/dui70/DirectUI/Parser/XmlParser.h
namespace DirectUI
{
	// Forward declaration of unexported class
	class DUIParsePlayer;
	class DUIParseRecorder;

	typedef HRESULT (CALLBACK *PLAYTCREATE)(int, int*, Value** ppVal);

	enum DynamicScaleParsing
	{
		DSP_None = 0,
		DSP_Enabled = 1
	};

	typedef enum _DUI_PARSE_STATE
	{
		DPS_CalculateStringLength = 0,
		DPS_GlobalAllocStringCopy = 1,
		DPS_GlobalLockStringCopy = 2,
		DPS_StringCopy = 3,
		DPS_CreateXmlReaderFromHGlobal = 4,
		DPS_CreateStreamOnHGlobal = 5,
		DPS_CreateXmlReader = 6,
		DPS_CreateXmlReaderInputWithEncodingName = 7,
		DPS_SetInput = 8,
		DPS_InitializeParserFromXmlLiteReader = 9,
		DPS_CreateBinaryXmlReader = 10,
		DPS_BuildStylesFromBinary = 11,
		DPS_ReadyOnBinarySource = 12
	} DUI_PARSE_STATE;

	struct LINEINFO
	{
		WORD iLine;
		WORD iCol;
	};

	enum LogicalOperators
	{
		PSLO_NULL = 0,
		PSLO_Equal = 1,
		PSLO_NotEqual = 2,
		PSLO_Greater = 3,
		PSLO_GreaterEqual = 4,
		PSLO_Lesser = 5,
		PSLO_LesserEqual = 6
	};

	struct XMLParserCond
	{
		LogicalOperators nLogOp;
		WCHAR* szProp;
		WCHAR* szVal;
	};

	namespace ParserTools
	{
		enum ExprNodeType
		{
			ENT_LITERAL = 0,
			ENT_STRING = 1,
			ENT_FUNCALL = 2,
			ENT_OR = 3
		};

		struct ExprNode
		{
			ExprNodeType ent;
			WCHAR* pszName;
			UINT cArgs;
			ExprNode* pArgs;
			UINT uiArgs;
		};

		enum TokenType
		{
			ttInvalid = 0,
			ttLiteral = 1,
			ttString = 2,
			ttEOI = 3
		};

		class Tokenizer
		{
		public:
			void Initialize(WCHAR*);
			TokenType Next();
			WCHAR PeekChar();
			void SkipChar(WCHAR);
			WCHAR* CurrentName();
			bool IsWhiteSpace(WCHAR);
			bool IsLiteralChar(WCHAR wch);
			void SkipWhiteSpace();

		private:
			WCHAR* _psz;
			WCHAR* _pszLast;
			WCHAR _wchSave;
		};

		class ValueParser : Tokenizer
		{
		public:
			ValueParser();
			~ValueParser();
			static HRESULT WINAPI Create(ValueParser** ppvp);
			void Destroy();
			HRESULT Parse(const WCHAR* pszValue, const ExprNode** ppenRoot);

		private:
			HRESULT Initialize();
			HRESULT ParseWorker();
			HRESULT ParseFuncall();
			HRESULT ParseOr();
			HRESULT FinishComplexNodeT(UINT uiFirstArgT);
			HRESULT AddExprNodeT(ExprNodeType);
			HRESULT InsertExprNodeT(ExprNodeType ent, int iDelta);
			HRESULT TransferNodes(UINT uiStartT);
			void ResetBuf();
			DynamicArray<ExprNode>* _pdaNodes;
			DynamicArray<ExprNode>* _pdaNodesT;
			WCHAR* _pszBuf;
			WCHAR _szBuf[260];
		};


		struct ClassicValue
		{
			const WCHAR* pszClass;
			int iPart;
			int iState;
			int iProp;
			const Value* pvParsed;
			const ExprNode* pen;
		};
	}

	typedef Value* (CALLBACK* PXMLGETSHEETCB)(const WCHAR*, void* pContext);
	typedef void (CALLBACK* PXMLPARSEERRORCB)(const WCHAR* pszError, const WCHAR* pszToken, int dLine, void* pContext);
	typedef bool (CALLBACK* PUNKNOWNATTRCB)(const WCHAR*, void* pContext);

    #if 1 // MODMOD: Imported pure methods.
    class DUIXmlParser;
    HRESULT (WINAPI *DUIXmlParser_Create)(DUIXmlParser** ppParserOut, PXMLGETSHEETCB pfnGetSheetCallback, void* pGetSheetContext, PXMLPARSEERRORCB pfnErrorCallback, void* pErrorContext);
    void (__thiscall *DUIXmlParser_Destroy)(DUIXmlParser *pThis);
    HRESULT (__thiscall *DUIXmlParser_SetXML)(DUIXmlParser *pThis, const WCHAR* pBuffer, HINSTANCE hResourceInstance, HINSTANCE hControlsInstance);
    HRESULT (__thiscall *DUIXmlParser_CreateElement)(DUIXmlParser *pThis, const WCHAR* pszResID, Element* pEleSubstitute, Element* pParent, DWORD* pdwDeferCookie, Element** ppElementOut);
    #endif // MODMOD
	class UILIB_API DUIXmlParser
	{
	public:
		DUIXmlParser();
		DUIXmlParser(const DUIXmlParser& other) = default;

		virtual ~DUIXmlParser();

		static HRESULT WINAPI Create(DUIXmlParser** ppParserOut, PXMLGETSHEETCB pfnGetSheetCallback, void* pGetSheetContext, PXMLPARSEERRORCB pfnErrorCallback, void* pErrorContext)
        { // MODMOD: Call pure method implementation.
            return DUIXmlParser_Create(ppParserOut, pfnGetSheetCallback, pGetSheetContext, pfnErrorCallback, pErrorContext);
        }
		void Destroy()
        { // MODMOD: Call pure method implementation.
            return DUIXmlParser_Destroy(this);
        }

		HRESULT _InitializeTables();
		void _DestroyTables();

		HRESULT SetXML(const WCHAR* pBuffer, HINSTANCE hResourceInstance, HINSTANCE hControlsInstance)
        { // MODMOD: Call pure method implementation.
            return DUIXmlParser_SetXML(this, pBuffer, hResourceInstance, hControlsInstance);
        }
		HRESULT SetPreprocessedXML(const WCHAR* pPreProcessed, HINSTANCE hResourceInstance, HINSTANCE hControlsInstance);
		HRESULT SetXMLFromResourceWithTheme(UINT uRCID, HINSTANCE hResInstance, HINSTANCE hResTheme, HINSTANCE hControlsInstance);
		HRESULT SetXMLFromResource(const WCHAR* pszResource, const WCHAR* pszResType, HINSTANCE hResourceInstance, HINSTANCE hControlsInstance);
		HRESULT SetXMLFromResource(const WCHAR* pszResid, HINSTANCE hResInstance, HINSTANCE hControlsInstance);
		HRESULT SetXMLFromResource(UINT uRCID, const WCHAR* pszResType, HINSTANCE hResInstance, HINSTANCE hControlsInstance);
		HRESULT SetXMLFromResource(UINT uRCID, HINSTANCE hResInstance, HINSTANCE hControlsInstance);

		void SetRootWindowForTheming(HWND);
		Value* GetMappedValue(WCHAR*);

		HRESULT CreateElement(const WCHAR* pszResID, Element* pEleSubstitute, Element* pParent, DWORD* pdwDeferCookie, Element** ppElementOut)
        { // MODMOD: Call pure method implementation.
            return DUIXmlParser_CreateElement(this, pszResID, pEleSubstitute, pParent, pdwDeferCookie, ppElementOut);
        }

		HRESULT GetSheet(const WCHAR* pszResID, Value** ppValueOut);

		void SetParseErrorCallback(PXMLPARSEERRORCB pfnErrorCallback, void* pContext);
		void SetGetSheetCallback(PXMLGETSHEETCB pfnGetSheetCallback, void* pContext);

		PXMLGETSHEETCB GetGetSheetCallback();
		void* GetSheetContext();
		void EnableDesignMode();
		void SetUnknownAttrCallback(PUNKNOWNATTRCB pfnUnknownAttrCallback, void* pContext);
		HINSTANCE GetResourceHInstance();
		HINSTANCE GetHInstance();
		HRESULT LookupElement(LINEINFO li, const WCHAR* pszElem, HINSTANCE hControlsInstance, IClassInfo** ppciOut);
		HRESULT LookupElement(IXmlReader* pReader, const WCHAR* pszElem, HINSTANCE hInstance, IClassInfo** ppciOut);
		HRESULT UpdateSheets(Element* pe);

		void SetDefaultHInstance(HINSTANCE hInst);
		void SetUnavailableIcon(HICON hIcon);
		void SetScaleFactor(float scaleFactor);
		void SetDynamicScaling(DynamicScaleParsing dsp);
		bool IsDynamicScaling();
		HRESULT CopySheets(DynamicArray<Value*>** ppdaSheets);
		void SetOverrideScaleFactor(float scaleFactor);
		bool GetOverrideScaleFactor(float* pScaleFactor) const;

	protected:
		HRESULT Initialize();
		HRESULT InitializeParserFromXmlReader(IXmlReader* pReader, HINSTANCE hResourceInstance, HINSTANCE hControlsInstance);

		HRESULT ParseStyleSheets(IXmlReader* pReader);
		HRESULT ParseStyleSheets();

		HRESULT _EnterOnCurrentThread();
		void _LeaveOnCurrentThread();

		static HRESULT WINAPI GetXmlLiteDll(HMODULE* phXmlLiteDll);
		HRESULT CreateXmlReader(IXmlReader** ppReader);
		HRESULT CreateXmlReaderFromHGLOBAL(HGLOBAL hglob, IXmlReader** ppReader);
		HRESULT CreateXmlReaderInputWithEncodingName(IStream* pInput, const WCHAR* pszEncodingName, IUnknown** ppReaderInput);

		HRESULT _SetXMLFromResource(const WCHAR* pszResource, const WCHAR* pszResType, HINSTANCE hResourceInstance, HINSTANCE hControlsInstance, HINSTANCE hResTheme);
		HRESULT _SetBinaryXml(const BYTE* pBuffer, UINT cbBuffer, HINSTANCE hControlsInstance);
		HRESULT _BuildFromBinary(Element* peSub, Element* peParent, const WCHAR* pszResource, DWORD* pdwDefer, Element** ppElement);
		HRESULT _BuildElement(IXmlReader* pReader, Element* peParent, Element** ppElement);
		HRESULT _BuildChildren(IXmlReader* pReader, Element* peParent);
		HRESULT _SetProperties(IXmlReader* pReader, IClassInfo* pClassInfo, Element* peTarget);
		HRESULT _ParseLayout(const WCHAR* pszLayoutString, Value** ppvLayout);
		HRESULT _ParseBehavior(Element* pTarget, const WCHAR* pszBehavior);
		HRESULT _CreateValue(const WCHAR* pszValue, const PropertyInfo* pPropInfo, Value** ppValue);
		HRESULT _GetClassForElement(IXmlReader* pReader, IClassInfo** ppClassInfo);
		HRESULT _GetClassForElementByName(const WCHAR* pszName, IClassInfo** ppClassInfo);
		HRESULT _GetPropertyForAttribute(IXmlReader* pReader, IClassInfo* pClassInfo, const PropertyInfo** ppPropInfo);
		HRESULT _BuildStyles(IXmlReader* pReader);
		HRESULT _GetValueForStyleSheet(IClassInfo* pClassInfo, const WCHAR* pszName, const WCHAR* pszValue, const PropertyInfo** ppPropInfo, Value** ppValue);
		LINEINFO _GetLineInfo(IXmlReader* pReader);
		HRESULT _SetupParserState(HINSTANCE hResourceInstance, HINSTANCE hControlsInstance);

		HRESULT _RecordElementTrees(IXmlReader* pReader);
		HRESULT _RecordElementWithChildren(IXmlReader* pReader, bool fEmptyElem, WCHAR** ppszElemName);
		HRESULT _RecordInstantiateElement(IXmlReader* pReader, WCHAR** ppszElemName);
		HRESULT _RecordSetElementProperties(IXmlReader* pReader);
		HRESULT _RecordElementLayout(IXmlReader* pReader, const WCHAR* pszValue);
		HRESULT _RecordElementBehaviors(IXmlReader* pReader, const WCHAR* pszValue);
		HRESULT _RecordSetValue(IXmlReader* pReader, const WCHAR* pszName, const WCHAR* pszValue);
		HRESULT _RecordElementStyleSheet(const WCHAR* pszSheetName, bool fIgnoreMissingSheet);

		HRESULT CreateStyleSheet(IXmlReader* pReader, const WCHAR* pszSheetResid, StyleSheet** ppSheet);
		HRESULT AddRulesToStyleSheet(IXmlReader* pReader, StyleSheet* pSheet, const WCHAR* pszSheetResid, DynamicArray<XMLParserCond>* pdaXMLConds, DynamicArray<WCHAR*>* pdaCondStrings);
		HRESULT _ResolveStyleSheet(const WCHAR* pszReference, Value** ppvSheet, UINT* pSheetId);


		HRESULT MapPropertyNameToPropertyInfo(LINEINFO li, IClassInfo* pci, const WCHAR* pszName, const PropertyInfo** ppInfo);
		HRESULT GetPropValPairInfo(LINEINFO li, IClassInfo* pci, const WCHAR* pszProperty, const WCHAR* pszValue, const PropertyInfo** ppInfo, Value** ppValue);
		HRESULT GetPropValPairInfo(IXmlReader* pReader, IClassInfo* pci, const WCHAR* pszProperty, const WCHAR* pszValue, const PropertyInfo** ppInfo, Value** ppValue);

		HRESULT _ParseValue(const PropertyInfo* ppi, WCHAR* pszValue, Value** ppValue);

		void SendParseError(const WCHAR* pszError, const WCHAR* pszToken, int dLine, int dCol, HRESULT hr);
		void SendParseError(const WCHAR* pszError, const WCHAR* pszToken, IXmlReader* pReader, HRESULT hr);
		int QuerySysMetric(int idx, bool* pfDynamicScaling);
		const WCHAR* QuerySysMetricStr(int idx, WCHAR* pszMetric, UINT c);

		template <typename T>
		struct UILIB_API FunctionDefinition
		{
			typedef HRESULT (*FUNCPARSER)(const ParserTools::ExprNode* pen, T*, bool*);

			const WCHAR* pszName;
			FUNCPARSER pfnParse;
		};

		static const FunctionDefinition<int> s_fdInt[3];
		static const FunctionDefinition<COLORREF> s_fdClr[4];
		static const FunctionDefinition<Value*> s_fdString[4];
		static const FunctionDefinition<ScaledRECT> s_fdRect[3];
		static const FunctionDefinition<ScaledSIZE> s_fdSize[3];
		static const FunctionDefinition<Value*> s_fdFill[4];
		static const FunctionDefinition<Value*> s_fdGraphic[5];

		struct NUMBER
		{
			int i;
			bool fDynamicScaling;
		};

		union ParsedArg
		{
			NUMBER number;
			LPCWSTR psz;
			COLORREF clr;
			HTHEME htheme;
			HMODULE hmod;
			HINSTANCE hinst;
			const ParserTools::ExprNode* pen;
		};

		HRESULT ParseArgs(const ParserTools::ExprNode* pen, ParsedArg* rgpa, UINT cpa, const CHAR* pszSignature);
		HRESULT ParseFunction(const WCHAR* pszName, const ParserTools::ExprNode* pen, ParsedArg* rgpa, UINT cpa, const CHAR* pszSignature);

		static bool WINAPI IsThemeClassName(const ParserTools::ExprNode* pen);

		HRESULT ParseMagnitude(const WCHAR* pszMag, int* pMagOut, bool* pfDynamicScaling);
		HRESULT ParseMagnitudeFloat(const WCHAR* pszMag, float* pMagOut, bool* pfDynamicScaling);

		HRESULT ParseLiteralNumber(const WCHAR* psz, int* pnOut, bool* pfDynamicScaling);
		HRESULT ParseColorInt(const WCHAR*, int*); // @Note: Not exported
		HRESULT ParseLiteralColorInt(const WCHAR* pszValue, int* piOut);
		HRESULT ParseLiteralColor(const WCHAR* pszValue, COLORREF* pclrOut);

		HRESULT ParseSysMetricInt(const ParserTools::ExprNode* pen, int* piOut, bool* pfDynamicScaling);
		HRESULT ParseGTMetInt(const ParserTools::ExprNode* pen, int* piOut, bool* pfDynamicScaling);

		HRESULT ParseARGBColor(const ParserTools::ExprNode* pen, COLORREF* pclrOut, bool* pfDynamicScaling);
		HRESULT ParseRGBColor(const ParserTools::ExprNode* pen, COLORREF* pclrOut, bool* pfDynamicScaling);
		HRESULT ParseGTCColor(const ParserTools::ExprNode* pen, COLORREF* pclrOut, bool* pfDynamicScaling);

		HRESULT ParseResStr(const ParserTools::ExprNode* pen, Value** ppVal, bool* pfDynamicScaling);
		HRESULT ParseSysMetricStr(const ParserTools::ExprNode* pen, Value** ppVal, bool* pfDynamicScaling);
		HRESULT ParseGTFStr(const ParserTools::ExprNode* pen, Value** ppVal, bool* pfDynamicScaling);

		HRESULT ParseRectRect(const ParserTools::ExprNode* pen, ScaledRECT* prcOut, bool* pfDynamicScaling);
		HRESULT ParseGTMarRect(const ParserTools::ExprNode* pen, ScaledRECT* prcOut, bool* pfDynamicScaling);

		HRESULT ParseSizeSize(const ParserTools::ExprNode* pen, ScaledSIZE* pszOut, bool* pfDynamicScaling);
		HRESULT ParseGTPartSize(const ParserTools::ExprNode* pen, ScaledSIZE* pszOut, bool* pfDynamicScaling);

		HRESULT ParseSGraphicHelper(bool fGraphic, const ParserTools::ExprNode* pen, Value** ppVal);
		HRESULT ParseSGraphicGraphic(const ParserTools::ExprNode* pen, Value** ppVal, bool* pfDynamicScaling);

		HRESULT ParseGraphicHelper(bool fGraphic, const ParserTools::ExprNode* pen, Value** ppVal);
		HRESULT ParseGraphicGraphic(const ParserTools::ExprNode* pen, Value** ppVal, bool* pfDynamicScaling);

		HRESULT ParseImageGraphic(const ParserTools::ExprNode* pen, Value** ppVal, bool* pfDynamicScaling);
		HRESULT ParseIconGraphic(const ParserTools::ExprNode* pen, Value** ppVal, bool* pfDynamicScaling);

		HRESULT ParseLiteral(const ParserTools::ExprNode* pen, const WCHAR** ppszOut);
		HRESULT ParseNumber(const ParserTools::ExprNode* pen, int* pnOut, bool* pfDynamicScaling);
		HRESULT ParseFloat(const ParserTools::ExprNode* pen, float* pflOut, bool* pfDynamicScaling);
		HRESULT ParseColor(const ParserTools::ExprNode* pen, COLORREF* pclrOut);
		HRESULT ParseQuotedString(const ParserTools::ExprNode* pen, WCHAR** ppszOut);
		HRESULT ParseResid(const ParserTools::ExprNode* pen, const WCHAR** ppszOut);
		HRESULT ParseTheme(const ParserTools::ExprNode* pen, bool use96dpi, HTHEME* phtheme);
		HRESULT ParseLibrary(const ParserTools::ExprNode* pen, HMODULE* phmod);

		HRESULT ParseRect(const ParserTools::ExprNode* pen, ScaledRECT* prcOut);
		HRESULT ParseSize(const ParserTools::ExprNode* pen, ScaledSIZE* pszOut);

		HRESULT ParseGradientFill(const ParserTools::ExprNode* pen, Value** ppVal, bool* pfDynamicScaling);
		HRESULT ParseDFCFill(const ParserTools::ExprNode* pen, Value** ppVal, bool* pfDynamicScaling);
		HRESULT ParseDTBFill(const ParserTools::ExprNode* pen, Value** ppVal, bool* pfDynamicScaling);

		HRESULT CreateLayout(const ParserTools::ExprNode* pen, PLAYTCREATE pfnCreate);

		HRESULT ParseIntValue(const ParserTools::ExprNode* pen, Value** ppVal);
		HRESULT ParseFloatValue(const ParserTools::ExprNode* pen, Value** ppVal);
		HRESULT ParseBoolValue(const ParserTools::ExprNode* pen, Value** ppVal);
		HRESULT ParseStringValue(const ParserTools::ExprNode* pen, Value** ppVal);
		HRESULT ParseRectValue(const ParserTools::ExprNode* pen, Value** ppVal);
		HRESULT ParseSizeValue(const ParserTools::ExprNode* pen, Value** ppVal);
		HRESULT ParsePointValue(const ParserTools::ExprNode* pen, Value** ppVal);
		HRESULT ParseFillValue(const ParserTools::ExprNode* pen, Value** ppVal);
		HRESULT ParseLayoutValue(const ParserTools::ExprNode* pen);
		HRESULT ParseGraphicValue(const ParserTools::ExprNode* pen, Value** ppVal);
		HRESULT ParseSheetValue(const ParserTools::ExprNode* pen, Value** ppVal);
		HRESULT ParseAtomValue(const ParserTools::ExprNode* pen, Value** ppVal);
		HRESULT ParseCursorValue(const ParserTools::ExprNode* pen, Value** ppVal);

		HRESULT ParseBehaviorArgValue(const ParserTools::ExprNode* pen, Value** ppVal);
		HRESULT ParseBehavior(const ParserTools::ExprNode* pen);
		HRESULT ParseDoubleListValue(const ParserTools::ExprNode* pen, Value** ppVal);

		HRESULT MapPropertyEnumValue(const EnumMap* pMap, const WCHAR* pszValue, int* piVal);
		HRESULT GetValueParser(ParserTools::ValueParser** ppvp);
		void ReturnValueParser(ParserTools::ValueParser* pvp);
		HRESULT GetParserCommon(DUIXmlParser** ppParserCommon);

		HMODULE _hXmlLiteDll;
		HINSTANCE _hControlsInstance;
		HANDLE _hDefault;
		HICON _hUnavailableIcon;

		PXMLPARSEERRORCB _pfnErrorCB;
		PXMLGETSHEETCB _pfnGetSheetCB;
		PUNKNOWNATTRCB _pfnUnknownAttrCallback;

		void* _pErrorContext;
		void* _pGetSheetContext;
		void* _pfnUnknownAttrContext;

		DynamicScaleParsing _dynamicScaleParsing;
		float _flScaleFactor;
		bool _fScaleFactorSet;
		bool _fParseErrorSent;
		bool _fDesignMode;
		int _fThemed;
		int _fHighContrast;
		int _fComposited;
		bool _fOverrideScale;

		const PropertyInfo* _ppiValue;
		const WCHAR* _pszError;

		ParserTools::ValueParser* _pvpCache;
		DynamicArray<Value*>* _pdaSheetList;
		DynamicArray<Value*>* _pdaTrackedValues;
		DUIXmlParser* _pParserCommon;
		IXmlReader* _pCurrentReader;

#if 1 // MODMOD: Stubbed types we don't really need.
        struct IDuiParserCache {};
        struct IDuiBinaryReader {};
        struct ResourceModuleHandles { static long volatile g_cRefCount; };
#endif // MODMOD
		IDuiParserCache* _pParserCache;
		IDuiBinaryReader* _pBinaryReader;

		int _nCreateDepth;

		DynamicArray<int>* _prgLayoutArgs;

	private:
		float _ScaleRelativePixels(float nRelPix);
		int _ScaleRelativePixels(int nRelPix);
		float _ScalePointsToPixels(float flPoint);
		int _ScalePointsToPixels(int nPoint);

		DUIParseRecorder* _pRecorder;
		DynamicArray<DUIParsePlayer*>* _prgPlayers;
		void SetParseState(DUI_PARSE_STATE eParseState);
		DUI_PARSE_STATE _eParseState;
		ResourceModuleHandles _rmhResourcesModules;
		DWORD _dwThreadId;
		ULONG _cRefThread;
		HWND _rootWindowForTheming;
	};

	class DUIFactory
	{
	public:
		UILIB_API DUIFactory(HWND hwnd);
		UILIB_API ~DUIFactory();
		UILIB_API DUIFactory& operator=(DUIFactory const&);

		UILIB_API HRESULT CreateParser();

		UILIB_API HRESULT LoadFromBuffer(const WCHAR* pszBuf, UINT cchBuf, const WCHAR* pszResid, Element* pParent, DWORD* pdwDeferCookie, Element** ppe);
		UILIB_API HRESULT LoadFromFile(const WCHAR*, const WCHAR*, Element*, unsigned long*, Element* *);
		UILIB_API HRESULT LoadFromResource(HINSTANCE, const WCHAR*, const WCHAR*, Element*, unsigned long*, Element* *, const WCHAR*);

		UILIB_API void SetError(const WCHAR*, ...);

		UILIB_API DUIXmlParser* DetachParser();
		UILIB_API DUIXmlParser* GetParser();

	private:
		UILIB_API static void WINAPI s_XMLParseError(const WCHAR* pszError, const WCHAR* pszToken, int dLine, DUIFactory* pContext);
		UILIB_API void ClearParser();

		int _fError;
		HINSTANCE _hInst;
		DUIXmlParser* _pParser;
		HWND _hwndParent;
	};
}

// world-windows-federation/dui70/DirectUI/SafeElementPtr.h
template <typename T>
class CSafeElementPtrBase : protected DirectUI::IElementListener
{
public:
	operator T*() const { return _pe; }
	T* operator->() const { return _pe; }
	bool operator!() const { return !_pe; }
	bool operator!=(T* pe) const { return _pe != pe; }
	bool operator==(T* pe) const { return _pe == pe; }

	CSafeElementPtrBase(const CSafeElementPtrBase&) = delete;

protected:
	CSafeElementPtrBase()
		: _pe(nullptr)
	{
	}

	CSafeElementPtrBase(int)
	{
		// Function body unknown
	}

	HRESULT _Assign(T* pe)
	{
		HRESULT hr = E_INVALIDARG;
		if (pe)
		{
			_pe = pe;
			hr = pe->AddListener(this);
			if (FAILED(hr))
			{
				_pe = nullptr;
			}
		}

		return hr;
	}

	//~ Begin DirectUI::IElementListener Interface
	void OnListenerAttach(DirectUI::Element* peFrom) override {}
	void OnListenerDetach(DirectUI::Element* peFrom) override { if (_pe) _pe = nullptr; }
	bool OnListenedPropertyChanging(DirectUI::Element* peFrom, const DirectUI::PropertyInfo* ppi, int iIndex, DirectUI::Value* pvOld, DirectUI::Value* pvNew) override { return true; }
	void OnListenedPropertyChanged(DirectUI::Element* peFrom, const DirectUI::PropertyInfo* ppi, int iIndex, DirectUI::Value* pvOld, DirectUI::Value* pvNew) override {}
	void OnListenedInput(DirectUI::Element* peFrom, DirectUI::InputEvent* pInput) override {}
	void OnListenedEvent(DirectUI::Element* peFrom, DirectUI::Event* pEvent) override {}
	//~ End DirectUI::IElementListener Interface

	T* _pe;

private:
	T** operator&() = delete;
};

template <typename T>
class CSafeElementPtr : public CSafeElementPtrBase<T>
{
	CSafeElementPtr(T* pe)
	{
		this->_Assign(pe); // Function body assumed
	}

	CSafeElementPtr(const CSafeElementPtr&) = delete;

public:
	CSafeElementPtr()
	{
	}

	CSafeElementPtr(int)
	{
		// Function body unknown
	}

	~CSafeElementPtr()
	{
		Unassign();
	}

	HRESULT Assign(T* pe)
	{
		Unassign();
		return this->_Assign(pe);
	}

	void Unassign()
	{
		if (this->_pe)
		{
			this->_pe->RemoveListener(this);
			this->_pe = nullptr;
		}
	}

	void DestroyAndUnassign()
	{
		if (this->_pe)
		{
			this->_pe->Destroy(true);
		}
		Unassign();
	}

	CSafeElementPtr* AddressOfClass()
	{
		return this;
	}
};

template <typename T>
class CSafeElementListenerPtr : public CSafeElementPtrBase<T>
{
protected:
	enum CALLBACK_STATE
	{
		CBS_NONE = 0,
		CBS_INCALLBACK = 1,
		CBS_INDETACH = 2,
	};

private:
	CSafeElementListenerPtr(T*) = delete;
	CSafeElementListenerPtr(const CSafeElementListenerPtr&) = delete;

public:
	CSafeElementListenerPtr()
		: _pselcbOwner(nullptr)
		, _cbs(CBS_NONE)
	{
	}

	// ReSharper disable once CppPossiblyUninitializedMember
	CSafeElementListenerPtr(int)
	{
	}

	~CSafeElementListenerPtr()
	{
		ReleaseListener();
	}

	HRESULT AssignListener(T* pe, CSafeElementListenerCB* pselcbOwner)
	{
		HRESULT hr = E_FAIL;

		if (_cbs == CBS_NONE)
		{
			ReleaseListener();
			_pselcbOwner = pselcbOwner;
			hr = this->_Assign(pe);
			if (FAILED(hr))
			{
				_pselcbOwner = nullptr;
			}
		}

		return hr;
	}

	void ReleaseListener()
	{
		if (_cbs == CBS_NONE)
		{
			if (this->_pe)
			{
				this->_pe->RemoveListener(this);
				if (this->_pe)
				{
					OnListenerDetach(this->_pe);
				}
			}
		}
		else
		{
			if (_cbs == CBS_INDETACH)
			{
				this->_pe = nullptr;
			}
			_pselcbOwner = nullptr;
		}
	}

protected:
	//~ Begin DirectUI::IElementListener Interface
	void OnListenerAttach(DirectUI::Element* peFrom) override
	{
		if (_pselcbOwner)
		{
			_cbs = CBS_INCALLBACK;
			_pselcbOwner->OnListenerAttach(peFrom);
			_cbs = CBS_NONE;
		}
	}

	void OnListenerDetach(DirectUI::Element* peFrom) override
	{
		if (this->_pe)
		{
			this->_pe = nullptr;
		}
	}

	bool OnListenedPropertyChanging(DirectUI::Element* peFrom, const DirectUI::PropertyInfo* ppi, int iIndex, DirectUI::Value* pvOld, DirectUI::Value* pvNew) override
	{
		bool fRet = false;

		if (_pselcbOwner)
		{
			_cbs = CBS_INCALLBACK;
			fRet = _pselcbOwner->OnListenedPropertyChanging(peFrom, ppi, iIndex, pvOld, pvNew);
			_cbs = CBS_NONE;
		}

		return fRet;
	}

	void OnListenedPropertyChanged(DirectUI::Element* peFrom, const DirectUI::PropertyInfo* ppi, int iIndex, DirectUI::Value* pvOld, DirectUI::Value* pvNew) override
	{
		if (_pselcbOwner)
		{
			_cbs = CBS_INCALLBACK;
			_pselcbOwner->OnListenedPropertyChanged(peFrom, ppi, iIndex, pvOld, pvNew);
			_cbs = CBS_NONE;
		}
	}

	void OnListenedInput(DirectUI::Element* peFrom, DirectUI::InputEvent* pInput) override
	{
		if (_pselcbOwner)
		{
			_cbs = CBS_INCALLBACK;
			_pselcbOwner->OnListenedInput(peFrom, pInput);
			_cbs = CBS_NONE;
		}
	}

	void OnListenedEvent(DirectUI::Element* peFrom, DirectUI::Event* pEvent) override
	{
		if (_pselcbOwner)
		{
			_cbs = CBS_INCALLBACK;
			_pselcbOwner->OnListenedEvent(peFrom, pEvent);
			_cbs = CBS_NONE;
		}
	}
	//~ End DirectUI::IElementListener Interface

	CSafeElementListenerCB* _pselcbOwner;
	CALLBACK_STATE _cbs;
};

// Private reversal by Allie (not upstreamed)
class CElementWithIUnknown
	: public DirectUI::Element
	, public IUnknown
{
public:
	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv) override;
	STDMETHODIMP_(ULONG) AddRef() override;
	STDMETHODIMP_(ULONG) Release() override;

	static HRESULT Create(DirectUI::Element *pParent, DWORD *pdwDeferCookie, DirectUI::Element **ppElement);

	static DirectUI::IClassInfo *Class;
	DirectUI::IClassInfo *GetClassInfo() override;
	static HRESULT Register();

	static IUnknown *GetUnknownFromElement(Element *pe);
};

extern const IID IID_IFrameManager;

class CElementWithSite
	: public CElementWithIUnknown
	, public IObjectWithSite
{
public:
	STDMETHODIMP QueryInterface(REFIID, void **) override;
	STDMETHODIMP_(ULONG) AddRef() override;
	STDMETHODIMP_(ULONG) Release() override;

	STDMETHODIMP SetSite(IUnknown *punkSite) override;
	STDMETHODIMP GetSite(REFIID riid, void **ppvSite) override;

	static HRESULT Create(DirectUI::Element *pParent, DWORD *pdwDeferCookie, DirectUI::Element **ppElement);

	static DirectUI::IClassInfo *Class;
	DirectUI::IClassInfo *GetClassInfo() override { return Class; }
	static HRESULT Register();

	HRESULT GetPersistStream(int, unsigned long, IStream **);

protected:
	~CElementWithSite();

	IUnknown *_punkSite;
};

// =====================================================================================
//
//    You are now at the end of the DirectUI headers section.
//
// =============================== /END DIRECTUI HEADERS ===============================

EXTERN_C NTSYSAPI NTSTATUS NTAPI RtlGetVersion(PRTL_OSVERSIONINFOW lpVersionInformation);
RTL_OSVERSIONINFOW g_osvi;

// Weak check
#define OS_IS_WINDOWS_8_0 (g_osvi.dwBuildNumber > 9000 && g_osvi.dwBuildNumber < 9400)

struct CDefView;

// XXX(kawapure): This is a __thiscall on x86-32 for some reason.
// Probably just fastcall.
int (__thiscall *IsLibrary)(IShellItem*);

// XXX(kawapure): Ditto IsLibrary.
int (__thiscall *IsInLibrary)(IShellItem*);

long (__fastcall *GetRootLibraryFromItem)(IUnknown*, IUnknown**);

long (__thiscall *CDefView_Init)(CDefView*, IShellFolder*);

ATOM (WINAPI *StrToID)(LPCWSTR);

long (__thiscall *Element_SetLayoutPos)(DirectUI::Element*, int);

long (__thiscall *Element_SetContentString)(DirectUI::Element *, LPCWSTR);

UID (WINAPI *Button_Click)() = nullptr;

#ifndef _WIN64
long (__fastcall *CDUIView_Create)(HWND,
                                  HWND,
                                  DirectUI::Element *,
                                  unsigned long*,
                                  DirectUI::Element **);
#else
long (*CDUIView_Create)(HWND,
                                  HWND,
                                  DirectUI::Element *,
                                  unsigned long*,
                                  DirectUI::Element **);
#endif

using Microsoft::WRL::ComPtr;

// -------------------------
// Helper functions
// -------------------------

[[nodiscard]] bool IsExplorerWindow(HWND hwnd)
{
    wchar_t windowClass[MAX_PATH] = { 0 };

    if (SUCCEEDED(RealGetWindowClassW(hwnd, windowClass, ARRAYSIZE(windowClass))))
    {
        if (0 == StrCmpI(L"CabinetWClass", windowClass)
        ||  0 == StrCmpI(L"ExplorerWClass", windowClass)
        ||  0 == StrCmpI(L"#32770", windowClass))
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Get the owner window of a DirectUI element.
 */
[[nodiscard]] HWND GetDuiElementOwnerWindow(DirectUI::Element &element)
{
    DirectUI::Element *pCurrent = &element;
    do
    {
        if (IsSubclassOf<DirectUI::ElementWithHWND>(pCurrent))
        {
            return static_cast<DirectUI::ElementWithHWND *>(pCurrent)->GetHWND();
        }
    }
    while ((pCurrent = pCurrent->GetParent()));

    return nullptr;
}

/**
 * @brief Get the owner Explorer window of a HWND.
 */
[[nodiscard]] HWND FindOwnerExplorerWindow(HWND hwndFirst)
{
    HWND hwndCurrent = hwndFirst;
    do
    {
        if (IsExplorerWindow(hwndCurrent))
        {
            return hwndCurrent;
        }
    }
    while ((hwndCurrent = GetParent(hwndCurrent)));

    return nullptr;
}

/**
 * @brief Get the owner Explorer window of a DirectUI element.
 */
[[nodiscard]] HWND FindDuiElementOwnerExplorerWindow(DirectUI::Element &element)
{
    return FindOwnerExplorerWindow(GetDuiElementOwnerWindow(element));
}

enum class LibraryFolderType
{
    NotLibrary,
    CentralLibrariesFolder,
    LibraryFolder,
    LibrarySubfolder,
    HomeGroupRoot,
    HomeGroupLibraries,
};

// Undocumented export from shell32.
HRESULT (__fastcall *GetParentAndChildIDListFromItem)(
    IShellItem *pShellItem,
    // XXX(kawapure): This is an ABI difference I don't care to look into to
    // explain why this code works. Just trust that it does.
    FOR_64_32(
        IID iid,
        const IID *iid
    ),
    IUnknown **punk,
    IUnknown **ppUnkOut
);

// Internal structure used by CSplitButton in shell32.
// public: long __cdecl ExplorerCommandItem::Init(struct IExplorerCommand *,struct IUnknown *,struct IShellItemArray *,int)
HRESULT (__thiscall *ExplorerCommandItem__Init)(
    struct ExplorerCommandItem *pExploreCommandItem,
    IExplorerCommand *pExplorerCommand,
    IUnknown *punk,
    IShellItemArray *pShellItemArray,
    int stateThing
);
struct ExplorerCommandItem
{
    GUID guidCanonicalName;
    EXPCMDFLAGS flags;
    EXPCMDSTATE state;
    LPWSTR szTitle;
    LPWSTR szTooltip;
    int cachedImageIndex;

    HRESULT Init(
        IExplorerCommand *pExplorerCommand,
        IUnknown *punk,
        IShellItemArray *pShellItemArray,
        int stateThing
    )
    {
        return ExplorerCommandItem__Init(this, pExplorerCommand, punk, pShellItemArray, stateThing);
    }

    ~ExplorerCommandItem()
    {
        if (szTitle)
            CoTaskMemFree(szTitle);
        if (szTooltip)
            CoTaskMemFree(szTooltip);
    }
};

HRESULT (__thiscall *CSplitButton__SetItem)(
    class CSplitButton *pThis,
    IUnknown *punk,
    const ITEMID_CHILD *pItem,
    const ExplorerCommandItem *pCommandItem,
    IServiceProvider *pServiceProvider
);

HRESULT (__fastcall *CSplitButton__Create)(
    DirectUI::Element *pWhatever,
    unsigned long whatever2,
    CSplitButton **ppElementOut,
    int whatever3
);

class CSplitButton : public DirectUI::Element
{
public:
    static HRESULT Create(
        DirectUI::Element *pWhatever,
        unsigned long whatever2,
        CSplitButton **ppElementOut,
        int whatever3
    )
    {
        return CSplitButton__Create(pWhatever, whatever2, ppElementOut, whatever3);
    }

    HRESULT SetItem(
        IUnknown *punk,
        const ITEMID_CHILD *pItem,
        const ExplorerCommandItem *pCommandItem,
        IServiceProvider *pServiceProvider
    )
    {
        return CSplitButton__SetItem(this, punk, pItem, pCommandItem, pServiceProvider);
    }
};

struct IElementTransfer
{
    virtual void TransferArrangementSplitButton(CSplitButton *p) = 0;
    virtual void TransferParentFolderLayoutElement(DirectUI::Element *p) = 0;
    virtual void TransferLibraryHeaderContainerElement(DirectUI::Element *p) = 0;
};

// Forward declared to be used in the constructor of LibraryHeader.
LRESULT CALLBACK DestroyWindowSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, DWORD_PTR uIdSubclass);

thread_local bool g_libraryManageUiOpen = false;

/**
 * @brief Controller class for the library headers.
 *
 * @details
 *      This class is responsible for managing the entire library headers UI and
 *      all associated state.
 *
 *      An instance is created and associated with each explorer window for the
 *      window's lifetime.
 */
struct LibraryHeader : IElementTransfer
{
    HWND _hwnd = nullptr;
    CDefView* _pDefView = nullptr;

    wchar_t *_pLibraryName = nullptr;

    CSafeElementPtr<DirectUI::Element> _pLibraryHeaderContainerElement;
    CSafeElementPtr<DirectUI::Element> _pParentFolderLayoutElement;
    CSafeElementPtr<DirectUI::Element> _pLibraryTitleElement;
    CSafeElementPtr<DirectUI::Element> _pLibraryDescriptionElement;
    CSafeElementPtr<DirectUI::Element> _pLocationCountElement;
    CSafeElementPtr<DirectUI::Element> _pArrangeByContainerElement;
    CSafeElementPtr<DirectUI::Element> _pTopViewPrefixElement;
    CSafeElementPtr<CSplitButton> _pArrangementSplitButtonElement;

    ComPtr<IShellFolder> _shellFolder = nullptr;
    ComPtr<IShellItem> _pShellItem = nullptr;
    ComPtr<IShellItem> _pRootShellItem = nullptr;
    ComPtr<IShellLibrary> _pShellLibrary = nullptr;
    ComPtr<IShellItemArray> _pShellItemArray = nullptr;

    LibraryFolderType _folderType = LibraryFolderType::NotLibrary;

    class ClickLocationsEventListener : public DirectUI::IElementListener
    {
        LibraryHeader *pLibraryHeader = nullptr;
    public:

        ClickLocationsEventListener(LibraryHeader *pOwner)
            : pLibraryHeader(pOwner)
        {
        }

        virtual ~ClickLocationsEventListener()
        {
        }

        void OnListenerAttach(DirectUI::Element* element) override
        {
        }

        void OnListenerDetach(DirectUI::Element* element) override
        {
        }

        bool OnListenedPropertyChanging(
            DirectUI::Element* peFrom,
            const DirectUI::PropertyInfo* ppi,
            int iIndex,
            DirectUI::Value* pvOld,
            DirectUI::Value* pvNew
        ) override
        {
            return true;
        }

        void OnListenedPropertyChanged(
            DirectUI::Element* peFrom,
            const DirectUI::PropertyInfo* ppi,
            int iIndex,
            DirectUI::Value* pvOld,
            DirectUI::Value* pvNe
        ) override
        {
        }

        void HandleClick()
        {
            if (pLibraryHeader->_pShellItem)
            {
                g_libraryManageUiOpen = true;
                SHShowManageLibraryUI(
                    pLibraryHeader->_pShellItem.Get(),
                    pLibraryHeader->_hwnd,
                    NULL,
                    NULL,
                    LMD_DEFAULT
                );
                g_libraryManageUiOpen = false;

                if (FAILED(pLibraryHeader->_pShellLibrary->LoadLibraryFromItem(pLibraryHeader->_pShellItem.Get(), STGM_READ)))
                {
                    return;
                }

                if (!pLibraryHeader->_pShellLibrary)
                {
                    return;
                }

                if (FAILED(pLibraryHeader->_pShellLibrary->GetFolders(LFF_ALLITEMS, IID_IShellItemArray, (void**)&pLibraryHeader->_pShellItemArray)))
                {
                    return;
                }

                if (!pLibraryHeader->_pShellItemArray)
                {
                    return;
                }

                DWORD locationCount = 0;

                if (FAILED(pLibraryHeader->_pShellItemArray->GetCount(&locationCount)))
                {
                    return;
                }

                pLibraryHeader->SetLocationCountText(locationCount);
            }
        }

        void OnListenedEvent(DirectUI::Element* element, DirectUI::Event* ev) override
        {
            if (Button_Click() == ev->uidType)
            {
                HandleClick();
            }
        }

        void OnListenedInput(DirectUI::Element* element, DirectUI::InputEvent* ev) override
        {
        }
    };

    // This is constructed from outside with new. It is owned by this structure,
    // so it will be freed when the structure is deleted.
    ClickLocationsEventListener *_pLocationClickEvent = nullptr;

    LibraryHeader(HWND hwnd)
        : _hwnd(hwnd)
    {
        CoCreateInstance(CLSID_ShellLibrary, NULL, CLSCTX_INPROC_SERVER,
                        IID_PPV_ARGS(&_pShellLibrary));
        CoCreateInstance(CLSID_ShellItem, NULL, CLSCTX_INPROC_SERVER,
                        IID_PPV_ARGS(&_pShellItem));
        CoCreateInstance(CLSID_ShellItem, NULL, CLSCTX_INPROC_SERVER,
                        IID_PPV_ARGS(&_pRootShellItem));
        CoCreateInstance(IID_IShellItemArray, NULL, CLSCTX_INPROC_SERVER,
                        IID_PPV_ARGS(&_pShellItemArray));
        CoCreateInstance(IID_IShellFolder, NULL, CLSCTX_INPROC_SERVER,
                        IID_PPV_ARGS(&_shellFolder));

        // Set up location click event, which is universally applicable so it
        // stays the same for the lifetime of the library header manager.
        _pLocationClickEvent = new ClickLocationsEventListener(this);

        // We will also subclass the HWND that owns this instance so that we
        // can detect when it's deleted. The subclass procedure will handle
        // the destruction of this class.
        WindhawkUtils::SetWindowSubclassFromAnyThread(
            hwnd, DestroyWindowSubclassProc, (DWORD_PTR)this);
    }

    ~LibraryHeader()
    {
        if (_pLocationCountElement && _pLocationClickEvent)
        {
            _pLocationCountElement->RemoveListener(_pLocationClickEvent);
            delete _pLocationClickEvent;
        }
    }

    void TransferArrangementSplitButton(CSplitButton *p) override
    {
        _pArrangementSplitButtonElement.Assign(p);
    }

    void TransferParentFolderLayoutElement(DirectUI::Element *p) override
    {
        _pParentFolderLayoutElement.Assign(p);
    }

    void TransferLibraryHeaderContainerElement(DirectUI::Element *p) override
    {
        _pLibraryHeaderContainerElement.Assign(p);
    }

    void SetLocationCountText(int locationCount)
    {
        wchar_t locationCountStr[MAX_PATH] = { 0 };

        if (locationCount == 1)
        {
            wcscpy_s(locationCountStr, GetUIStrings().locationSingular);
        }
        else
        {
            RUNTIME_ASSERT(SUCCEEDED(StringCchPrintf(
                locationCountStr, 
                MAX_PATH, 
                GetUIStrings().locationPlural, 
                locationCount
            )), "Failed to format plural location text.");
        }

        RUNTIME_ASSERT(
            SUCCEEDED(Element_SetContentString(
                _pLocationCountElement,
                locationCountStr)
            ),
            "Failed to set location count text."
        );
    }

    HRESULT SetupComInterfacesForShellFolder()
    {
        if (!_shellFolder)
        {
            return false;
        }

        ComPtr<IPersistFolder2> pPersistFolder2 = nullptr;

        if (FAILED(_shellFolder->QueryInterface(IID_IPersistFolder2, (void**)&pPersistFolder2)))
        {
            return false;
        }

        if (!pPersistFolder2)
        {
            return false;
        }

        ITEMIDLIST *pCurrentIdList = nullptr;

        if (FAILED(pPersistFolder2->GetCurFolder(&pCurrentIdList)))
        {
            return false;
        }

        if (!pCurrentIdList)
        {
            return false;
        }

        if (FAILED(SHCreateItemFromIDList(pCurrentIdList, IID_IShellItem, (void**)&_pShellItem)))
        {
            return false;
        }

        if (!_pShellItem)
        {
            return false;
        }

        return true;
    }

    bool GetLibraryPaneDescendents()
    {
        _pLibraryTitleElement.Unassign();
        _pLibraryDescriptionElement.Unassign();
        _pLocationCountElement.Unassign();
        _pArrangeByContainerElement.Unassign();

        if (!_pLibraryHeaderContainerElement)
        {
            // HACKHACK: This function is entered even in the case of folders
            // where this element doesn't exist at all, such as the fonts folder
            // and programs and features. In order to avoid a crash, we need to
            // return now.
            return false;
        }

        _pLibraryTitleElement.Assign(_pLibraryHeaderContainerElement->FindDescendent(
            StrToID(L"LibTitle")
        ));

        if (!_pLibraryTitleElement)
        {
            return false;
        }

        _pLibraryDescriptionElement.Assign(
            _pLibraryHeaderContainerElement->FindDescendent(
                StrToID(L"LibDesc")
            )
        );

        if (!_pLibraryDescriptionElement)
        {
            return false;
        }

        _pLocationCountElement.Assign(_pLibraryHeaderContainerElement->FindDescendent(
            StrToID(L"locationcount")
        ));

        if (!_pLocationCountElement)
        {
            return false;
        }

        _pArrangeByContainerElement.Assign(
            _pLibraryHeaderContainerElement->FindDescendent(
                StrToID(L"ArrangeByContainer")
            )
        );

        if (!_pArrangeByContainerElement)
        {
            return false;
        }

        _pTopViewPrefixElement.Assign(
            _pArrangeByContainerElement->FindDescendent(
                StrToID(L"TopViewPrefix")
            )
        );

        if (_pTopViewPrefixElement)
        {
            Element_SetContentString(_pTopViewPrefixElement, GetUIStrings().arrangeBy);
        }

        return true;
    }

    bool SetLibPaneForLibFolder()
    {
        if (!_pLibraryName)
        {
            return false;
        }

        wchar_t libraryPaneTitle[MAX_PATH] = { 0 };
        if (FAILED(StringCchPrintf(libraryPaneTitle, MAX_PATH, 
            GetUIStrings().folderTitle, _pLibraryName)))
        {
            return false;
        }

        if (FAILED(Element_SetContentString(_pLibraryTitleElement, libraryPaneTitle)))
        {
            return false;
        }

        if (FAILED(Element_SetContentString(_pLibraryDescriptionElement,
            GetUIStrings().folderIncludesLabel)))
        {
            return false;
        }

        if (!_pShellItemArray)
        {
            return false;
        }

        DWORD locationCount = 0;
        if (FAILED(_pShellItemArray->GetCount(&locationCount)))
        {
            return false;
        }

        SetLocationCountText(locationCount);

        if (FAILED(_pLocationCountElement->SetVisible(true)))
        {
            return false;
        }

        if (FAILED(_pArrangeByContainerElement->SetVisible(true)))
        {
            return false;
        }

        if (nullptr != _pLocationClickEvent)
        {
            _pLocationCountElement->RemoveListener(_pLocationClickEvent);

            if (FAILED(_pLocationCountElement->AddListener(_pLocationClickEvent)))
            {
                return false;
            }
        }

        if (FAILED(Element_SetLayoutPos(_pLibraryHeaderContainerElement, DirectUI::BLP_Top)))
        {
            return false;
        }
        return true;
    }

    bool SetLibPaneForLibChildFolder()
    {
        if (!_pLibraryName)
        {
            return false;
        }
        if (FAILED(Element_SetContentString(_pLibraryDescriptionElement, _pLibraryName)))
        {
            return false;
        }

        if (FAILED(_pRootShellItem->GetDisplayName(SIGDN_NORMALDISPLAY, &_pLibraryName)))
        {
            return false;
        }

        wchar_t libraryPaneTitle[MAX_PATH] = { 0 };
        if (FAILED(StringCchPrintf(
            libraryPaneTitle, MAX_PATH, GetUIStrings().folderTitle,
            _pLibraryName)))
        {
            return false;
        }

        if (FAILED(Element_SetContentString(_pLibraryTitleElement, libraryPaneTitle)))
        {
            return false;
        }

        if (FAILED(_pLocationCountElement->SetVisible(false)))
        {
            return false;
        }

        if (FAILED(_pArrangeByContainerElement->SetVisible(true)))
        {
            return false;
        }

        if (FAILED(Element_SetLayoutPos(_pLibraryHeaderContainerElement, DirectUI::BLP_Top)))
        {
            return false;
        }
        return true;
    }

    bool SetLibPaneForHomeFolder(LPCWSTR title, LPCWSTR description)
    {
        if (FAILED(Element_SetContentString(_pLibraryTitleElement, title)))
        {
            return false;
        }

        if (FAILED(Element_SetContentString(_pLibraryDescriptionElement,
            description)))
        {
            return false;
        }

        if (FAILED(_pLocationCountElement->SetVisible(false)))
        {
            return false;
        }

        if (FAILED(_pArrangeByContainerElement->SetVisible(false)))
        {
            return false;
        }

        if (FAILED(Element_SetLayoutPos(_pLibraryHeaderContainerElement, DirectUI::BLP_Top)))
        {
            return false;
        }

        return true;
    }

    bool SetLibPaneForLibHome()
    {
        return SetLibPaneForHomeFolder(
            GetUIStrings().homeTitle,
            GetUIStrings().homeDescription
        );
    }

    bool SetLibPaneForHomegroupRoot()
    {
        return SetLibPaneForHomeFolder(
            GetUIStrings().homegroupTitle,
            GetUIStrings().homegroupRootDescription
        );
    }

    bool SetLibPaneForHomegroupLibraries()
    {
        return SetLibPaneForHomeFolder(
            GetUIStrings().homegroupTitle,
            GetUIStrings().homegroupLibrariesDescription
        );
    }

    // Reverse engineered from 7
    // shell32!CLibraryPaneModuleInner::_InitializeTopViewControl
    HRESULT InitializeTopViewControl()
    {
        IShellItem *pShellItem;
        HRESULT hr = SHCreateItemFromParsingName(
            // This shell item controls the arrange by behavior. It's in the
            // Command Folder alongside the entries for the view menu that shows
            // on the command bar.
            L"shell:::{437ff9c0-a07f-4fa0-af80-84b6c6440a16}\\{ab0b0ad7-8dbb-470f-998d-4999464ae6de}",
            0,
            IID_PPV_ARGS(&pShellItem)
        );

        if (SUCCEEDED(hr))
        {
            IShellFolder *pCommandFolder;
            IShellItem *pArrangementItem;
            hr = GetParentAndChildIDListFromItem(
                pShellItem,
                FOR_64_32(IID_IShellFolder, &IID_IShellFolder),
                (IUnknown **)&pCommandFolder,
                (IUnknown **)&pArrangementItem
            );
            if (SUCCEEDED(hr))
            {
                ExplorerCommandItem *pCommandItem = new (std::nothrow) ExplorerCommandItem();
                hr = nullptr == pCommandItem ? E_OUTOFMEMORY : S_OK;
                if (pCommandItem)
                {
                    IExplorerCommand *pExplorerCommand;
                    hr = pShellItem->BindToHandler(
                        nullptr,
                        BHID_SFObject,
                        IID_PPV_ARGS(&pExplorerCommand));
                    if (SUCCEEDED(hr))
                    {
                        // MODMOD: This class doesn't have a site, so I replaced
                        // the this->punkSite access of the original with a
                        // straight _pDefView reference. This seems to just work.
                        hr = pCommandItem->Init(
                            pExplorerCommand,
                            (IUnknown *)_pDefView,
                            nullptr,
                            0
                        );
                        if (SUCCEEDED(hr))
                        {
                            hr = _pArrangementSplitButtonElement->SetItem(
                                pCommandFolder,
                                (const ITEMIDLIST *)pArrangementItem,
                                pCommandItem,
                                nullptr
                            );

                            if (SUCCEEDED(hr))
                            {
                                DirectUI::Element *pActionButtonEl =
                                    _pArrangementSplitButtonElement
                                        ->FindDescendent(
                                            StrToID(L"ActionButton")
                                        );
                                pActionButtonEl->SetAccValue(
                                    pCommandItem->szTitle
                                );
                            }
                        }
                        pExplorerCommand->Release();
                    }
                    delete pCommandItem;
                }

                CoTaskMemFree(pArrangementItem);
                pCommandFolder->Release();
            }

            pShellItem->Release();
        }

        return hr;
    }
};

std::vector<LibraryHeader*> g_existingLibraryPanes;

[[nodiscard]] int GetWindowMapIndexOfHwnd(HWND hwnd)
{
    RUNTIME_ASSERT(IsExplorerWindow(hwnd), "Window must be an explorer window");

    for (size_t i = 0; i < g_existingLibraryPanes.size(); i++)
    {
        if (g_existingLibraryPanes[i]->_hwnd == hwnd)
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}

[[nodiscard]] LibraryHeader *GetLibraryHeaderInfoForWindow(HWND hWnd)
{
    int index = GetWindowMapIndexOfHwnd(hWnd);

    if (index == -1)
    {
        return nullptr;
    }
    else
    {
        return g_existingLibraryPanes[index];
    }
}

LRESULT CALLBACK DestroyWindowSubclassProc(HWND hWnd,
                              UINT uMsg,
                              WPARAM wParam,
                              LPARAM lParam,
                              DWORD_PTR uIdSubclass)
{
    switch (uMsg)
    {
        case WM_DESTROY:
        {
            int i = GetWindowMapIndexOfHwnd(hWnd);
            if (i >= 0)
            {
                delete g_existingLibraryPanes[i];
                g_existingLibraryPanes.erase(g_existingLibraryPanes.begin() + i);
                Wh_Log(L"Received WM_DESTROY on HWND %p, so removed from list.", hWnd);
            }
            break;
        }
    }


    return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

DEFINE_TRANSITION_EXTRA_ARGS(CDefView_Init, CDUIView_Create, {
    CDefView *pDefView;
    IShellFolder *pShellFolder;
});

// For Windows 8.0 support.
static struct : IElementTransfer {
    CSplitButton *_pArrangementSplitButtonElement;
    DirectUI::Element *_pParentFolderLayoutElement;
    DirectUI::Element *_pLibraryHeaderContainerElement;

    void TransferArrangementSplitButton(CSplitButton *p) override
    {
        _pArrangementSplitButtonElement = p;
    }

    void TransferParentFolderLayoutElement(DirectUI::Element *p) override
    {
        _pParentFolderLayoutElement = p;
    }

    void TransferLibraryHeaderContainerElement(DirectUI::Element *p) override
    {
        _pLibraryHeaderContainerElement = p;
    }
} g_win8ElementTransfer;

long __thiscall CDefView_Init_Hook(CDefView* pDefView,
                        IShellFolder* pShellFolder)
{
    long ret = CDefView_Init(pDefView, pShellFolder);

    if (g_libraryManageUiOpen)
    {
        return ret;
    }

    SET_TRANSITION_EXTRA_ARGS_ALLOC(CDefView_Init, CDUIView_Create, {
        TRANSITION_EXTRA_ARG(pDefView = pDefView)
        TRANSITION_EXTRA_ARG(pShellFolder = pShellFolder)
    });

    return ret;
}

#if 1 // DEBUGDEBUG
void CALLBACK HandleDuiXmlParseError(const WCHAR* pszError, const WCHAR* pszToken, int dLine, void* pContext)
{
    Wh_Log(L"DUI Parse Error at line %d on token %s: %s", dLine, pszToken, pszError);
}
#endif // DEBUGDEBUG

/**
 * @brief
 *    Sets up the library header view when CDUIView::Create is called in
 *    Explorer.
 *
 * @details
 *    A new DUIView window is created every time the user navigates in Explorer,
 *    so this function is called continually throughout the lifetime of the mod.
 */
HRESULT __fastcall CDUIView_Create_Hook(HWND hwndOwner,
                          HWND duiViewHwnd,
                          DirectUI::Element *c,
                          unsigned long* d,
                          DirectUI::Element **ppElementOut)
{
    HRESULT ret = CDUIView_Create(hwndOwner, duiViewHwnd, c, d, ppElementOut);

    if (g_libraryManageUiOpen)
    {
        return ret;
    }

    Wh_Log(L"DUIView HWND: %p", OS_IS_WINDOWS_8_0 ? hwndOwner : duiViewHwnd);
    HWND hwnd = FindOwnerExplorerWindow(OS_IS_WINDOWS_8_0 ? hwndOwner : duiViewHwnd);
    Wh_Log(L"Owner explorer window HWND: %p", hwnd);
    if (!RUNTIME_ASSERT(hwnd, "Failed to find HWND."))
    {
        return ret;
    }

    LibraryHeader *pState = GetLibraryHeaderInfoForWindow(
        OS_IS_WINDOWS_8_0 ? duiViewHwnd : hwnd);
    if (OS_IS_WINDOWS_8_0)
    {
        LibraryHeader *pLibraryHeader = new LibraryHeader(hwnd);
        g_existingLibraryPanes.push_back(pLibraryHeader);
        pState = pLibraryHeader;

        Wh_Log(L"Set up explorer window %p.");
        
        auto transition = g_win8ElementTransfer;

        pState->TransferArrangementSplitButton(transition._pArrangementSplitButtonElement);
        pState->TransferParentFolderLayoutElement(transition._pParentFolderLayoutElement);
        pState->TransferLibraryHeaderContainerElement(transition._pLibraryHeaderContainerElement);

        transition = {};
    }
    else
    {
        if (!RUNTIME_ASSERT(pState, "Failed to get state."))
        {
            return ret;
        }
    }

    if (HAS_TRANSITION_EXTRA_ARGS(CDefView_Init, CDUIView_Create))
    {
        auto extraArgs = GET_TRANSITION_EXTRA_ARGS(CDefView_Init, CDUIView_Create);

        pState->_pDefView = extraArgs->pDefView;
        pState->_shellFolder = extraArgs->pShellFolder;

        FREE_TRANSITION_EXTRA_ARGS(CDefView_Init, CDUIView_Create);
    }

    if (!pState->SetupComInterfacesForShellFolder())
    {
        Wh_Log(L"Failed to set up COM interfaces for the current shell folder.");
        return ret;
    }

    if (!pState->GetLibraryPaneDescendents())
    {
        Wh_Log(L"Failed to get library pane descendents.");
        return ret;
    }

    ComPtr<IShellItem> pLibrariesShellItem;
    ComPtr<IShellItem> pHomeGroupShellItem;

    if (IsLibrary(pState->_pShellItem.Get()))
    {
        pState->_folderType = LibraryFolderType::LibraryFolder;

        if (FAILED(pState->_pShellItem->GetDisplayName(SIGDN_NORMALDISPLAY, &pState->_pLibraryName)))
        {
            Wh_Log(L"Failed to get the display name of the current shell item.");
            return ret;
        }

        if (!pState->_pShellLibrary)
        {
            Wh_Log(L"The shell is in a library folder, but _pShellLibrary is not set.");
            return ret;
        }

        if (FAILED(pState->_pShellLibrary->LoadLibraryFromItem(pState->_pShellItem.Get(), STGM_READ)))
        {
            Wh_Log(L"Failed LoadLibraryFromItem.");
            return ret;
        }

        if (FAILED(pState->_pShellLibrary->GetFolders(LFF_ALLITEMS, IID_PPV_ARGS(&pState->_pShellItemArray))))
        {
            Wh_Log(L"Failed to get library child folder shell items.");
            return ret;
        }

        if (FAILED(pState->InitializeTopViewControl()))
        {
            Wh_Log(L"Failed to initialize top view control.");
            return ret;
        }

        if (!pState->SetLibPaneForLibFolder())
        {
            Wh_Log(L"Failed to set up library pane for library folder.");
            return ret;
        }

        return ret;
    }
    else if (IsInLibrary(pState->_pShellItem.Get()))
    {
        pState->_folderType = LibraryFolderType::LibrarySubfolder;

        if (FAILED(pState->_pShellItem->GetDisplayName(SIGDN_NORMALDISPLAY, &pState->_pLibraryName)))
        {
            Wh_Log(L"Failed to get the display name of the current shell item.");
            return ret;
        }

        if (FAILED(GetRootLibraryFromItem(pState->_pShellItem.Get(), (IUnknown**)&pState->_pRootShellItem)))
        {
            Wh_Log(L"Failed to get the root shell item.");
            return false;
        }

        if (!pState->_pRootShellItem)
        {
            Wh_Log(L"The shell is in a library folder, but the root shell item is not set.");
            return false;
        }

        if (FAILED(pState->InitializeTopViewControl()))
        {
            Wh_Log(L"Failed to initialize top view control.");
            return ret;
        }

        if (!pState->SetLibPaneForLibChildFolder())
        {
            Wh_Log(L"Failed to set up library pane for library child folder.");
            return ret;
        }

        return ret;
    }

    if (SUCCEEDED(SHGetKnownFolderItem(
        FOLDERID_Libraries, KF_FLAG_DEFAULT, 0,
        IID_PPV_ARGS(&pLibrariesShellItem)
    )))
    {
        int comparisonResult = 0;
        if (S_OK == pLibrariesShellItem->Compare(
            pState->_pShellItem.Get(),
            SICHINT_CANONICAL,
            &comparisonResult
        ))
        {
            pState->_folderType = LibraryFolderType::CentralLibrariesFolder;

            if (!pState->SetLibPaneForLibHome())
            {
                Wh_Log(L"Failed to set up library pane for central libraries folder.");
                return ret;
            }

           return ret;
        }
    }

    if (SUCCEEDED(SHGetKnownFolderItem(
        FOLDERID_HomeGroup, KF_FLAG_DEFAULT, 0, 
        IID_PPV_ARGS(&pHomeGroupShellItem))))
    {
        int comparisonResult = 0;
        if (S_OK == pHomeGroupShellItem->Compare(
            pState->_pShellItem.Get(), 
            SICHINT_CANONICAL, 
            &comparisonResult))
        {
            pState->_folderType = LibraryFolderType::HomeGroupRoot;

            if (!pState->SetLibPaneForHomegroupRoot())
            {
                Wh_Log(L"Failed to set up library pane for homegroup root.");
                return ret;
            }

            return ret;
        }
        else
        {
            ComPtr<IShellItem> pParentShellItem = nullptr;
            if (SUCCEEDED(pState->_pShellItem->GetParent(&pParentShellItem)))
            {
                if (S_OK == pHomeGroupShellItem->Compare(
                    pParentShellItem.Get(),
                    SICHINT_CANONICAL,
                    &comparisonResult
                ))
                {
                    pState->_folderType = LibraryFolderType::HomeGroupLibraries;

                    if (!pState->SetLibPaneForHomegroupLibraries())
                    {
                        Wh_Log(L"Failed to set up library pane for homegroup root.");
                        return ret;
                    }

                    return ret;
                }
            }
        }
    }

    pState->_folderType = LibraryFolderType::NotLibrary;

    if (pState->_pLibraryHeaderContainerElement)
    {
        // Hide the library header:
        Element_SetLayoutPos(pState->_pLibraryHeaderContainerElement, DirectUI::LP_None);
    }

    return ret;
}

void DetectAndReportConflicts(
    HWND hwnd,
    DirectUI::Element *pFolderLayoutElement,
    const WCHAR *pszDescendentName)
{
    DirectUI::Element *pExistingLibraryHeader = 
        pFolderLayoutElement->FindDescendent(
            StrToID(pszDescendentName)
        );
    
    if (nullptr != pExistingLibraryHeader)
    {
        static thread_local bool s_hasWarnedBefore = false;

        if (!s_hasWarnedBefore)
        {
            MessageBoxW(
                hwnd,
                L"Another mod seems to be conflicting with the library headers "
                L"mod and resulting in multiple library header elements appearing "
                L"at the same time.\n\n"
                L"Please check for any mods which may serve a similar purpose.",
                L"Leymonaide's Library Pane Mod",
                MB_ICONWARNING | MB_OK
            );
            s_hasWarnedBefore = true;
        }
    }
}

HRESULT __thiscall DUIXmlParser_CreateElement_Hook(DirectUI::DUIXmlParser* pThis,
                                     LPCWSTR resid,
                                     DirectUI::Element *pParentElement,
                                     DirectUI::Element *idk,
                                     unsigned long* defKey,
                                     DirectUI::Element **ppFolderLayoutElement)
{
    HRESULT hr = DirectUI::DUIXmlParser_CreateElement(
        pThis,
        resid,
        pParentElement,
        idk,
        defKey,
        ppFolderLayoutElement
    );

    if (g_libraryManageUiOpen)
    {
        return hr;
    }

    DirectUI::Element *pFolderLayoutElement = *ppFolderLayoutElement;

    // If this is set, then we're working with a dialog window.
    DirectUI::Element *pDialogViewHostElement = nullptr;

    // For regular explorer windows, we always have an explicit FolderLayout.
    // It's a bit harder for ExplorerFrame dialog windows (open/save), which
    // must be detected using this path.
    bool isFolderLayout = (0 == wcscmp(resid, L"FolderLayout")) || (
        resid
        && 0 == wcscmp(resid, L"main")
        && pFolderLayoutElement
        && (pDialogViewHostElement = 
                pFolderLayoutElement->FindDescendent(StrToID(L"clientviewhost")))
    );

    if (pFolderLayoutElement && resid && isFolderLayout)
    {
        HWND hwnd2 = GetDuiElementOwnerWindow(*pParentElement);
        Wh_Log(L"direct parent element %p", hwnd2);
        HWND hwnd = FindDuiElementOwnerExplorerWindow(*pParentElement);

        IElementTransfer *pElementTransfer = nullptr;

        if (!OS_IS_WINDOWS_8_0)
        {
            if (!IsExplorerWindow(hwnd))
            {
                Wh_Log(L"Window %p is not an Explorer window.", hwnd);
                return hr;
            }

            pElementTransfer = GetLibraryHeaderInfoForWindow(hwnd);

            if (!pElementTransfer)
            {
                if (hwnd && IsExplorerWindow(hwnd))
                {
                    LibraryHeader *pLibraryHeader = new LibraryHeader(hwnd);
                    g_existingLibraryPanes.push_back(pLibraryHeader);
                    pElementTransfer = pLibraryHeader;

                    Wh_Log(L"Set up explorer window %p.", hwnd);
                }
            }
        }
        else
        {
            pElementTransfer = &g_win8ElementTransfer;
        }
        
        RUNTIME_ASSERT(pElementTransfer, "Missing element transfer object.");
        
        // Detect conflicts:
        DetectAndReportConflicts(hwnd, pFolderLayoutElement, 
            L"LeymonaideLibraryHeaderModule"); // Same mod
        DetectAndReportConflicts(hwnd, pFolderLayoutElement,
            L"LibraryHeaderModule");         // Older versions and similar mods.

        DirectUI::DUIXmlParser *pXmlParser = nullptr;
        HRESULT hr = DirectUI::DUIXmlParser::Create(&pXmlParser, nullptr, nullptr, HandleDuiXmlParseError, nullptr);
        if (!RUNTIME_ASSERT(SUCCEEDED(hr), "Failed to create DUIXML parser."))
        {
            Wh_Log(L"HR = %p", hr);
            return hr;
        }

        HINSTANCE hInst = GetModuleHandle(nullptr);

        if (!RUNTIME_ASSERT(
                SUCCEEDED(pXmlParser->SetXML(kLibraryPaneXml, hInst, hInst)
            ), "Failed SetXML."))
        {
            pXmlParser->Destroy();
            return hr;
        }

        CElementWithSite *pLibraryHeaderElement = nullptr;

        // The header should go right before the view host container. If it's
        // too early in the tree, then it will show above the navigation pane on
        // the left. If it's too late, then it'll show below the view host.
        DirectUI::Element *pInsertBeforeElement =
            pFolderLayoutElement->FindDescendent(
                StrToID(L"ViewHostContainer")
            );
        
        if (!pInsertBeforeElement && pDialogViewHostElement)
        {
            // If we're constructing for an ExplorerFrame dialog rather than a
            // full explorer window, then there will not be a view host
            // container. We will simply add it right before the parent of the
            // "clientviewhost" instead.
            //
            // The reason we add it before the parent and not the view host
            // itself is something to do with element layout. The parent is
            // functionally the same as a ViewHostContainer, but without an
            // ID to identify it. The container does layout for the actual
            // explorer view (I believe), so something happens to make the
            // library pane not show up. Thus, we want to put it before the
            // container as in the other natural case.
            pInsertBeforeElement = pDialogViewHostElement->GetParent();
        }
        else if (!pInsertBeforeElement)
        {
            // Otherwise, it's possible for no ViewHostContainer to exist, such
            // as in the event of opening the control panel. If this is the
            // case, then the element shouldn't be inserted.
            pXmlParser->Destroy();
            return hr;
        }

        DWORD dwDeferCookie = 0;
        if (!RUNTIME_ASSERT(
            SUCCEEDED(
                pXmlParser->CreateElement(
                    L"LibraryHeader",
                    nullptr,
                    pFolderLayoutElement,
                    &dwDeferCookie,
                    (DirectUI::Element **)&pLibraryHeaderElement
                )
            ),
            "Failed to create library header element."
        ))
        {
            pXmlParser->Destroy();
            return hr;
        }

        // Create the "arrange by" split button:
        CSplitButton *pSplitButton = nullptr;
        RUNTIME_ASSERT(
            SUCCEEDED(CSplitButton::Create(
                nullptr,
                0,
                &pSplitButton,
                0
            )),
            "Failed to create CSplitButton."
        );

        if (pSplitButton)
        {
            DirectUI::Element *pCommandElement = nullptr;
            RUNTIME_ASSERT(
                SUCCEEDED(
                    pXmlParser->CreateElement(
                        L"CommandElement",
                        pSplitButton,
                        nullptr,
                        0,
                        &pCommandElement
                    )
                ),
                "Failed to create CommandElement element."
            );

            DirectUI::Element *pTopViewControl =
                pLibraryHeaderElement->FindDescendent(StrToID(L"TopViewControl"));
            
            if (RUNTIME_ASSERT(
                SUCCEEDED(pTopViewControl->Insert((DirectUI::Element **)&pSplitButton, 1, 0)),
                "Failed to insert top view control."
            ))
            {
                pElementTransfer->TransferArrangementSplitButton(pSplitButton);
            }
        }
        
        // Insert creates a gap and pushes existing items at and after the
        // insertion point after that gap. As such, you just need to take the
        // index of the item to insert it before.
        int goodIndex = pInsertBeforeElement->GetIndex();

        // Aerexplorer modifies the UIFILE of shell32 to be flat, so inserting
        // it directly under the FolderLayout element worked. But Windows 10's
        // default UIFILE has it nested in an anonymous Element object. As such,
        // it's best to put it under the parent of the insert before element.
        RUNTIME_ASSERT(
            SUCCEEDED(pInsertBeforeElement->GetParent()->Insert(
                    (DirectUI::Element **)&pLibraryHeaderElement,
                    1,
                    goodIndex
                )
            ),
            "Failed to insert the library header element."
        );
        RUNTIME_ASSERT(SUCCEEDED(pLibraryHeaderElement->SetVisible(true)),
            "Failed to make the library header visible.");
        pLibraryHeaderElement->EndDefer(dwDeferCookie);

        pElementTransfer->TransferParentFolderLayoutElement(pFolderLayoutElement);
        pElementTransfer->TransferLibraryHeaderContainerElement(pLibraryHeaderElement);

        pXmlParser->Destroy();
    }
    return hr;
}

WindhawkUtils::SYMBOL_HOOK shell32Hooks[] =
{
    {
        {
            FOR_64_32(
                L"int __cdecl IsLibrary(struct IShellItem *)",
                L"int __stdcall IsLibrary(struct IShellItem *)"
            ),
            FOR_64_32(
                L"IsLibrary",
                L"_IsLibrary@4"
            ),
        },
        &IsLibrary,
        nullptr,
        false,
    },
    {
        {
            FOR_64_32(
               L"int __cdecl IsInLibrary(struct IShellItem *)",
               L"int __stdcall IsInLibrary(struct IShellItem *)"
            )
        },
        &IsInLibrary,
        nullptr,
        false,
    },
    {
        {
            FOR_64_32(
                L"GetRootLibraryFromItem",
                L"_GetRootLibraryFromItem@8"
            )
        },
        &GetRootLibraryFromItem,
        nullptr,
        false,
    },
    {
        {
            FOR_64_32(
                L"public: long __cdecl CDefView::Init(struct IShellFolder *)",
                L"public: long __thiscall CDefView::Init(struct IShellFolder *)"
            )
        },
        &CDefView_Init,
        CDefView_Init_Hook,
        false,
    },
    {
        {
            FOR_64_32(
                L"public: static long __cdecl CDUIView::Create(unsigned int,struct HWND__ *,class DirectUI::Element *,unsigned long *,class DirectUI::Element * *)",
                L"public: static long __stdcall CDUIView::Create(unsigned int,struct HWND__ *,class DirectUI::Element *,unsigned long *,class DirectUI::Element * *)"
            )
        },
        &CDUIView_Create,
        CDUIView_Create_Hook,
        false,
    },
    {
        {
            FOR_64_32(
                L"public: long __cdecl ExplorerCommandItem::Init(struct IExplorerCommand *,struct IUnknown *,struct IShellItemArray *,int)",
                L"public: long __thiscall ExplorerCommandItem::Init(struct IExplorerCommand *,struct IUnknown *,struct IShellItemArray *,int)"
            )
        },
        &ExplorerCommandItem__Init,
        nullptr,
    },
    {
        {
            FOR_64_32(
                L"public: long __cdecl CSplitButton::SetItem(struct IShellFolder *,struct _ITEMID_CHILD const __unaligned *,struct ExplorerCommandItem const *,struct IServiceProvider *)",
                L"public: long __thiscall CSplitButton::SetItem(struct IShellFolder *,struct _ITEMID_CHILD const *,struct ExplorerCommandItem const *,struct IServiceProvider *)"
            )
        },
        &CSplitButton__SetItem,
        nullptr,
    },
    {
        {
            FOR_64_32(
                L"public: static long __cdecl CSplitButton::Create(class DirectUI::Element *,unsigned long *,class DirectUI::Element * *,int)",
                L"public: static long __stdcall CSplitButton::Create(class DirectUI::Element *,unsigned long *,class DirectUI::Element * *,int)"
            )
        },
        &CSplitButton__Create,
        nullptr,
    },
    {

        {
            FOR_64_32(
                L"GetParentAndChildIDListFromItem",
                L"_GetParentAndChildIDListFromItem@16"
            )
        },
        &GetParentAndChildIDListFromItem,
        nullptr,
    },
};

WindhawkUtils::SYMBOL_HOOK dui70Hooks[] =
{
    {
        {
            FOR_64_32(
                L"public: long __cdecl DirectUI::DUIXmlParser::CreateElement(unsigned short const *,class DirectUI::Element *,class DirectUI::Element *,unsigned long *,class DirectUI::Element * *)",
                L"public: long __thiscall DirectUI::DUIXmlParser::CreateElement(unsigned short const *,class DirectUI::Element *,class DirectUI::Element *,unsigned long *,class DirectUI::Element * *)"
            )
        },
        &DirectUI::DUIXmlParser_CreateElement,
        DUIXmlParser_CreateElement_Hook,
        false,
    },
    {
        {
            FOR_64_32(
                L"public: class DirectUI::Element * __cdecl DirectUI::Element::FindDescendent(unsigned short)",
                L"public: class DirectUI::Element * __thiscall DirectUI::Element::FindDescendent(unsigned short)"
            )
        },
        &DirectUI::Element_FindDescendent,
        nullptr,
        false,
    },
    {
        {
            FOR_64_32(
                L"public: long __cdecl DirectUI::Element::SetLayoutPos(int)",
                L"public: long __thiscall DirectUI::Element::SetLayoutPos(int)"
            )
        },
        &Element_SetLayoutPos,
        nullptr,
        false,
    },
    {
        {
            FOR_64_32(
                L"public: class DirectUI::Element * __cdecl DirectUI::Element::GetParent(void)",
                L"public: class DirectUI::Element * __thiscall DirectUI::Element::GetParent(void)"
            )
        },
        &DirectUI::Element_GetParent,
        nullptr,
        true,
    },
    {
        {
            FOR_64_32(
                L"public: virtual struct DirectUI::IClassInfo * __cdecl DirectUI::ElementWithHWND::GetClassInfoW(void)",
                L"public: virtual struct DirectUI::IClassInfo * __thiscall DirectUI::ElementWithHWND::GetClassInfoW(void)"
            )
        },
        &__pfnGetClassInfoW,
        nullptr,
        true,
    },
    {
        {
            FOR_64_32(
                L"StrToID",
                L"_StrToID@4"
            )
        },
        &StrToID,
        nullptr,
        false,
    },
    {
        {
            FOR_64_32(
                L"public: long __cdecl DirectUI::Element::SetContentString(unsigned short const *)",
                L"public: long __thiscall DirectUI::Element::SetContentString(unsigned short const *)"
            )
        },
        &Element_SetContentString,
        nullptr,
        false,
    },
    {
        {
            FOR_64_32(
                L"public: long __cdecl DirectUI::Element::SetVisible(bool)",
                L"public: long __thiscall DirectUI::Element::SetVisible(bool)"
            )
        },
        &DirectUI::Element_SetVisible,
        nullptr,
        false,
    },
    {
        {
            FOR_64_32(
                L"public: long __cdecl DirectUI::Element::AddListener(struct DirectUI::IElementListener *)",
                L"public: long __thiscall DirectUI::Element::AddListener(struct DirectUI::IElementListener *)"
            )
        },
        &DirectUI::Element_AddListener,
        nullptr,
        false,
    },
    {
        {
            FOR_64_32(
                L"public: void __cdecl DirectUI::Element::RemoveListener(struct DirectUI::IElementListener *)",
                L"public: void __thiscall DirectUI::Element::RemoveListener(struct DirectUI::IElementListener *)"
            )
        },
        &DirectUI::Element_RemoveListener,
        nullptr,
        false,
    },
    {
        {
            FOR_64_32(
                L"public: void __cdecl DirectUI::Element::EndDefer(unsigned long)",
                L"public: void __thiscall DirectUI::Element::EndDefer(unsigned long)"
            )
        },
        &DirectUI::Element_EndDefer,
        nullptr,
        false,
    },
    {
        {
            FOR_64_32(
                L"public: int __cdecl DirectUI::Element::GetIndex(void)",
                L"public: int __thiscall DirectUI::Element::GetIndex(void)"
            )
        },
        &DirectUI::Element_GetIndex,
        nullptr,
        false,
    },
    {
        {
            FOR_64_32(
                L"public: long __cdecl DirectUI::Element::SetAccValue(unsigned short const *)",
                L"public: long __thiscall DirectUI::Element::SetAccValue(unsigned short const *)"
            )
        },
        &DirectUI::Element_SetAccValue,
        nullptr,
        false,
    },
    {
        {
            FOR_64_32(
                L"public: static class UID __cdecl DirectUI::Button::Click(void)",
                L"public: static class UID __stdcall DirectUI::Button::Click(void)"
            )
        },
        &Button_Click,
        nullptr,
        false,
    },
    {
        {
            FOR_64_32(
                L"public: static long __cdecl DirectUI::DUIXmlParser::Create(class DirectUI::DUIXmlParser * *,class DirectUI::Value * (__cdecl*)(unsigned short const *,void *),void *,void (__cdecl*)(unsigned short const *,unsigned short const *,int,void *),void *)",
                L"public: static long __stdcall DirectUI::DUIXmlParser::Create(class DirectUI::DUIXmlParser * *,class DirectUI::Value * (__stdcall*)(unsigned short const *,void *),void *,void (__stdcall*)(unsigned short const *,unsigned short const *,int,void *),void *)"
            )
        },
        &DirectUI::DUIXmlParser_Create,
        nullptr,
        false,
    },
    {
        {
            FOR_64_32(
                L"public: long __cdecl DirectUI::DUIXmlParser::SetXML(unsigned short const *,struct HINSTANCE__ *,struct HINSTANCE__ *)",
                L"public: long __thiscall DirectUI::DUIXmlParser::SetXML(unsigned short const *,struct HINSTANCE__ *,struct HINSTANCE__ *)"
            )
        },
        &DirectUI::DUIXmlParser_SetXML,
        nullptr,
        false,
    },
    {
        {
            FOR_64_32(
                L"public: void __cdecl DirectUI::DUIXmlParser::Destroy(void)",
                L"public: void __thiscall DirectUI::DUIXmlParser::Destroy(void)"
            )
        },
        &DirectUI::DUIXmlParser_Destroy,
        nullptr,
        false,
    },
};

void CALLBACK WilLogCallback(wil::FailureInfo const &failure) noexcept
{
    wchar_t message[2048];
    if (SUCCEEDED(wil::GetFailureLogString(message, ARRAYSIZE(message), failure)))
    {
        Wh_Log(L"%s", message);
    }
}

BOOL Wh_ModInit()
{
    Wh_Log(L"Init");
    HMODULE hShell32 = LoadLibrary(L"shell32.dll");
    HMODULE hDui70 = LoadLibrary(L"dui70.dll");

    wil::SetResultLoggingCallback(WilLogCallback);

    RtlGetVersion(&g_osvi);

    if (!WindhawkUtils::HookSymbols(hDui70, dui70Hooks, ARRAYSIZE(dui70Hooks)))
    {
        Wh_Log(L"Failed to hook symbols in dui70.dll.");
        return FALSE;
    }

    if (!WindhawkUtils::HookSymbols(hShell32, shell32Hooks, ARRAYSIZE(shell32Hooks)))
    {
        Wh_Log(L"Failed to hook symbols in shell32.dll");
        return FALSE;
    }

    return TRUE;
}

void Wh_ModUninit()
{
    Wh_Log(L"Uninit");
}

void Wh_ModSettingsChanged()
{
    Wh_Log(L"SettingsChanged");
}

//==============================================================================
// The resolved bugs section:
//

// BUGBUG(#1): Needs arrange by string.

// BUGBUG(#2): Does not work with explorer7 immersive mode, iirc this is also a
// known issue with the original mod by Ojas. If I had to guess, probably is an
// issue with the whole CreateWindow hooking approach which I eventually want to
// do away with in favor of a more versatile method anyways.
// UPDATE(2025-12-08): It is indeed an issue with CreateWindow hooking.
// FIXFIX(2025-12-09): It was an incompatibility with CoInitializeEx.
// Fortunately, by the time this mod is used, the shell will have initialized
// COM at an appropriate time anyways. Calling CoInitializeEx was not
// problematic under most circumstances, but it was in this particular instance
// for unknown reasons. I still do not understand why the CreateWindowEx hook
// was entering a recursion loop causing a stack overflow crash on ex7 either.