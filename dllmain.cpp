#include <random>
#include <windows.h>
#pragma warning(push, 0)
#include <cocos2d.h>
#pragma warning(pop)
#include "LoadingLayer.hpp"
#include "includes.h"
#include <windows.h>
#include <shellapi.h>
#include <MinHook.h>
#include <gd.h>
#include <ctime>
#include <thread>
#include <chrono>
#include "AnunciosLayer.hpp"

//ToMorritowCode

//Lo huviera hecho en geode pero no se como ejecutarle asiqxd

bool write_bytes(
    const std::uintptr_t address,
    std::vector<uint8_t> const& bytes)
{
    return WriteProcessMemory(
        GetCurrentProcess(),
        reinterpret_cast<LPVOID>(address),
        bytes.data(),
        bytes.size(),
        nullptr);
}

class AnuncioLayerw {
public:

    void Anuncios(cocos2d::CCObject* pSender) { AnunciosLayer::create()->show(); }

};

class EventoGDPS : public cocos2d::CCLayer {
public:
    void MostrarTexto(cocos2d::CCObject* pSender) {
        auto GM = gd::GameManager::sharedState();

        const char* mensaje = obtenerMensajeSegunFecha();
        auto owo = gd::FLAlertLayer::create(nullptr, "GDPS Announcement", "ok", nullptr, mensaje);
        owo->show();
    }

    void NivelTest(cocos2d::CCObject*) {

    int audio = 21; //Musica del Nivel...

    auto lvl = gd::GJGameLevel::create();

    lvl->setLevelData(""); ///Nivel Data... Puede ser cualquiera pero debes pegar ahi el LevelData

    lvl->m_nAudioTrack = audio;
    auto TerminoLvl = gd::PlayLayer::scene(lvl);
    auto director = cocos2d::CCDirector::sharedDirector();
    director->replaceScene(cocos2d::CCTransitionFade::create(0.5, TerminoLvl));

    lvl->m_eLevelType = gd::kGJLevelTypeSaved;
    lvl->m_bDontSave = true;
    lvl->m_sLevelName = "World";

    lvl->m_nStars = 5;
    lvl->m_nCoins = 3;
    lvl->m_nCoinsVerified = true;
    lvl->m_nStarRatings = 5;
    lvl->m_nRateFeature = 1;
    }

    const char* obtenerMensajeSegunFecha() {
        // Obtener la Fecha xd
        time_t now = time(0);
        struct tm* timeinfo = localtime(&now);

        // Verifica si es el 14 de noviembre >w<
        if (timeinfo->tm_mon == 10 && timeinfo->tm_mday == 14) {
            // Mensaje
            return "Hola como estan owo?";
        } else {
            // No es el 14 de noviembre unu, mensaje predeterminado
            return "No Todavia tenemos algo para usted .,.";
        }
    }

    void CreatorLayerowo(cocos2d::CCObject* pSender) {
    auto GM = gd::GameManager::sharedState();
    auto GM2 = gd::GJAccountManager::sharedState();

    if (GM2->m_nPlayerAccountID == 0) {
        // accountID_ está en 0 --- No te saldra el anuncio
        auto owo = gd::FLAlertLayer::create(nullptr, "GDPSWow", "ok", nullptr, "Necesitas una cuenta para entrar.");
        owo->show();

    } else {
        // ejecutar cuando el accountID_ es mayor que 0
        // Ejemplo: CuentaID: 0 -- no te sale el anuncion (no tienes cuenta).. --- CuentaID: 46345341 --- Te saldra esto xd
        this->runAction(CCSequence::create(CCDelayTime::create(2.70f), CCCallFuncO::create(this, callfuncO_selector(AnuncioLayerw::Anuncios), this), nullptr));
    }
    }
};

bool (__thiscall* MenuLayer_init)(CCLayer* self);
bool __fastcall MenuLayer_init_H(CCLayer* self, void*) {

    if (!MenuLayer_init(self)) return false;

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto SpritePlay = CCSprite::createWithSpriteFrameName("GJ_musicOnBtn_001.png");
    SpritePlay->setScale({1.0f});
    
    auto ButtonPlay = gd::CCMenuItemSpriteExtra::create(
        SpritePlay,
        self,
        menu_selector(EventoGDPS::CreatorLayerowo)
    );

    ButtonPlay->setPosition(winSize.width - ButtonPlay->getContentSize().width / 2, 
                        winSize.height - ButtonPlay->getContentSize().height / 2);

    auto MenuPlay = CCMenu::create();
    MenuPlay->addChild(ButtonPlay);
    MenuPlay->setPosition(-10, -10);
    self->addChild(MenuPlay);

    return true;
}

/* //Esto no vale quince intentar una peruanada xq
enum Meses {
    ENERO = 0,
    FEBRERO = 1,
    MARZO = 2,
    ABRIL = 3,
    MAYO = 4,
    JUNIO = 5,
    JULIO = 6,
    AGOSTO = 7,
    SEPTIEMBRE = 8,
    OCTUBRE = 9,
    NOVIEMBRE = 10,
    DICIEMBRE = 11
};

const char* obtenerMensajeDelDia(std::tm* tmp) {

    std::vector<std::pair<std::tm, const char*>> fechasEspeciales = {
        {{0, 0, 0, 1, 1, 0}, "Feliz Ano Nuevo :D!!!"},
        {{0, 0, 0, 14, 1, 0}, "Feliz dia de San Valentin Comunidad :D!"},
        {{0, 0, 0, 15, 3, 0}, "Feliz cumple ToMorritow :D!!"},
        {{0, 0, 0, 31, 10, 0}, "Feliz Halloween Owo!"},
        {{0, 0, 0, 24, 12, 0}, "Feliz Navidad Gente .D!"},
        {{0, 0, 0, 31, 12, 0}, "Poco para 2024 >w<!."},
        {{0, 0, 0, 12, 11, 0}, "Testeo XD"}
    };

    for (const auto& fecha : fechasEspeciales) {
        if (tmp != nullptr && std::memcmp(tmp, &fecha.first, sizeof(std::tm)) == 0) {
            return fecha.second;
        }
    }

    return nullptr;
}
*/

const char* obtenerMensajeAleatorio() {
    const char* messages[] = {
        "Recuerda leer las reglas >w<!",
        "Asegurate de unirte al servidor de Discord owo",
        "Bienvenido al GDPS uwu",
        "Sin ningún hacker por aquí...",
        "Bienvenido Aventurero OwO",
        "Ehh h bos bosteas el Servidor de Discord qwq!?...",
        "ToMorritow mi Jefe es muy amable pwp",
        "Te aseguro que no entraste al Servidor de Discord unu"
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, sizeof(messages) / sizeof(messages[0]) - 1);

    auto chosen_index = dist(gen);
    return messages[chosen_index];
}

const char* LoadingOwo() {

    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);

    if (timeinfo->tm_mon == 10 && timeinfo->tm_mday == 14) {

        return "OwO?";
    } else {

        return obtenerMensajeAleatorio();
    }
}

const char* (__thiscall* LoadingLayer_getString_org)(LoadingLayer*);
const char* __fastcall LoadingLayer_getString_h(LoadingLayer* self, void*) {

    return LoadingOwo();
}

DWORD WINAPI thread_func(void* hModule) {

    MH_Initialize();

    auto base = reinterpret_cast<uintptr_t>(GetModuleHandle(0));

    MH_CreateHook( // MenuLayer
        reinterpret_cast<void*>(base + 0x1907b0),
        reinterpret_cast<void*>(&MenuLayer_init_H),
        reinterpret_cast<void**>(&MenuLayer_init)
    );

    MH_CreateHook(
        reinterpret_cast<void*>(base + 0x18cf40),
        reinterpret_cast<void*>(&LoadingLayer_getString_h),
        reinterpret_cast<void**>(&LoadingLayer_getString_org)
    );

    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE handle, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        auto h = CreateThread(0, 0, thread_func, handle, 0, 0);
        if (h)
            CloseHandle(h);
        else
            return FALSE;
    }
    return TRUE;
}