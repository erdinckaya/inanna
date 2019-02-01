//
// Created by misterdortnal on 31.12.2018.
//

#ifndef MONITORX_MONITORX_H
#define MONITORX_MONITORX_H


#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <entityx/entityx.h>
#include <type_traits>

#include "3rdParty/ImGui/imgui.h"
#include "3rdParty/ImGui/imgui_impl_sdl.h"
#include "3rdParty/ImGui/imgui_impl_opengl2.h"
#include "3rdParty/FlexibleReflection/Reflect.h"


#ifndef __APPLE__
#include <climits>
#endif

struct end_of_list;

namespace monitorx {
    class MonitorX {
    public:
        MonitorX(entityx::EntityX *entityX, SDL_Window *window, SDL_GLContext *context) :
                entityX(entityX), window(window), context(context), showDemo(false),
                entityEditorFlag(false) {}

        ~MonitorX();

        void Init();

        void ProcessEvent(SDL_Event *event);

        void Destroy();

        void ShowDemo(bool value);

        void ShowEntityEditor(bool value);

        template<typename... Components>
        void Render() {
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL2_NewFrame();
            ImGui_ImplSDL2_NewFrame(window);
            ImGui::NewFrame();
            // Rendering


            //region IMGUI
            if (showDemo) {
                ImGui::ShowDemoWindow(&showDemo);
            }

            RenderEntityEditor<Components...>();
            //endregion

            // TODO: Add your ui to here!
            ImGui::Render();
            ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        }

    private:
        entityx::EntityX *entityX;
        SDL_Window *window;
        SDL_GLContext *context;

        entityx::Entity currentEntity;

        //region Flags
        bool showDemo;
        bool entityEditorFlag;
        //endregion


        template<typename... Components>
        void RenderEntityEditor() {
            if (!entityEditorFlag) {
                return;
            }

            ImGui::Begin("Entity Editor", &entityEditorFlag, 0);
            for (entityx::Entity entity : entityX->entities.entities_for_debugging()) {
                auto str = "Entity##" + std::to_string(entity.id().id());
                if (ImGui::CollapsingHeader(str.c_str())) {
                    currentEntity = entity;
                    RenderComponent<Components...>();
                }
            }
            ImGui::End();
        }

        template<typename C>
        void RenderComponent() {
            static_assert(std::is_same<C, end_of_list>::value, "error");
        }

        template<typename C, typename C1, typename... Components>
        void RenderComponent() {
            if (currentEntity.has_component<C>()) {
                auto obj = (const void *) currentEntity.component<C>().get();
                auto *typeDesc = dynamic_cast<reflect::TypeDescriptor_Struct *>(reflect::TypeResolver<C>::get());
                if (typeDesc != nullptr) {
                    RenderStruct(typeDesc, obj, std::to_string(currentEntity.id().id()), nullptr);
                }
            }

            RenderComponent<C1, Components...>();
        }

        void RenderFloat(const void *obj, const reflect::TypeDescriptor_Struct::Member &member,
                         const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &strID) const {
            ImGui::PushItemWidth(100);
            ImGui::DragFloat(strID.c_str(), (float *) ((char *) obj + member.offset),
                             0.02f, FLT_MIN, FLT_MAX, "%.2f", 2.0f);
        }

        void RenderInt(const void *obj, const reflect::TypeDescriptor_Struct::Member &member,
                       const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &strID) const {
            ImGui::PushItemWidth(100);
            ImGui::DragInt(strID.c_str(), (int *) ((char *) obj + member.offset),
                           0.02f, INT_MIN, INT_MAX, "%.2f");
        }

        void RenderDouble(const void *obj, const reflect::TypeDescriptor_Struct::Member &member,
                          const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &strID) const {
            ImGui::PushItemWidth(100);
            ImGui::DragFloat(strID.c_str(), (float *) ((char *) obj + member.offset),
                             0.02f, FLT_MIN, FLT_MAX, "%.2f", 2.0f);
        }

        void RenderString(const void *obj, const reflect::TypeDescriptor_Struct::Member &member,
                          const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &strID) const {
            ImGui::PushItemWidth(100);
            auto *str = (std::__1::string *) ((char *) obj + member.offset);
            ImGui::InputText(strID.c_str(), (char *) str->c_str(), str->capacity() + 1,
                             ImGuiInputTextFlags_CallbackResize, InputTextCallback, (void *) str);
        }

        void RenderBool(const void *obj, const reflect::TypeDescriptor_Struct::Member &member,
                        const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &strID) const {
            ImGui::Checkbox(strID.c_str(), (bool *) ((char *) obj + member.offset));
        }

        void RenderPrimitives(const void *obj, const reflect::TypeDescriptor_Struct::Member &member,
                        const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &strID) const {
            if (strcmp(member.type->type(obj).c_str(), "float") == 0) {
                RenderFloat(obj, member, strID);
            } else if (strcmp(member.type->type(obj).c_str(), "int") == 0) {
                RenderInt(obj, member, strID);
            } else if (strcmp(member.type->type(obj).c_str(), "double") == 0) {
                RenderDouble(obj, member, strID);
            } else if (strcmp(member.type->type(obj).c_str(), "string") == 0) {
                RenderString(obj, member, strID);
            } else if (strcmp(member.type->type(obj).c_str(), "bool") == 0) {
                RenderBool(obj, member, strID);
            }
        }

        void RenderStruct(reflect::TypeDescriptor_Struct *typeDesc, const void *obj, const std::string &idBase,
                          const char *recursiveName) {
            auto elemID = std::string(typeDesc->name) + "##" + idBase;
            if (recursiveName != nullptr) {
                elemID = std::string(recursiveName) + "##" + idBase;
            }

            if (ImGui::TreeNode(elemID.c_str())) {
                elemID = idBase + std::string(typeDesc->name);
                for (auto member : typeDesc->members) {
                    bool isStruct = false;
                    auto strID = std::string(member.name).append("##").append(elemID);

                    if (strcmp(member.type->type(obj).c_str(), "struct") == 0) {
                        isStruct = true;
                        const void *next_obj = ((char *) obj + member.offset);
                        std::string nextID = elemID.append(member.name);
                        RenderStruct(dynamic_cast<reflect::TypeDescriptor_Struct *>(member.type), next_obj, nextID,
                                     member.name);
                    } else if (strcmp(member.type->type(obj).c_str(), "vector") == 0) {
                        auto tD = dynamic_cast<reflect::TypeDescriptor_StdVector *>(member.type);
                        std::string nextID = std::string(member.name).append("##").append(elemID);
                        if (ImGui::TreeNode(nextID.c_str())) {
                            for (int i = 0; i < tD->getSize(obj); ++i) {
                                const void *next_obj = tD->getItem(obj, static_cast<size_t>(i) + member.offset);
                                nextID = nextID.append(std::to_string(i));
                                auto nextType = dynamic_cast<reflect::TypeDescriptor_Struct *>(tD->itemType);
                                const char *text = nullptr;
                                if (nextType != nullptr) {
                                    text = nextType->name;
                                    RenderStruct(nextType, next_obj, nextID, std::to_string(i).c_str());
                                } else {
                                    reflect::TypeDescriptor_Struct::Member m{};
                                    m.name = std::to_string(i).c_str();
                                    m.offset = 0;
                                    m.type = tD->itemType;
                                    RenderPrimitives(next_obj, m, std::to_string(i));
                                }

                                if (text != nullptr) {
                                    ImGui::SameLine(0);
                                    ImGui::Text("%s", text);
                                }
                            }
                            ImGui::TreePop();
                            ImGui::Separator();
                        }
                    } else {
                        RenderPrimitives(obj, member, strID);
                    }

                    ImGui::SameLine(0);
                    const char *text = member.type->type(obj).c_str();
                    if (isStruct) {
                        auto nextType = dynamic_cast<reflect::TypeDescriptor_Struct *>(member.type);
                        text = nextType->name;
                    }

                    ImGui::Text("%s", text);
                }

                ImGui::TreePop();
                ImGui::Separator();
            }
        }


        static int InputTextCallback(ImGuiInputTextCallbackData *data) {
            if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
                // Resize string callback
                auto *str = (std::string *) data->UserData;
                IM_ASSERT(data->Buf == str->c_str());
                str->resize(static_cast<unsigned long>(data->BufTextLen));
                data->Buf = (char *) str->c_str();
            }
            return 0;
        }
    };


}


#endif //MONITORX_MONITORX_H
