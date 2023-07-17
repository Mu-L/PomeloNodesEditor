// pomelo_node_editor.
#include <fstream>
#include <chrono>
#include <document.h> // RapidJSON

#include "pomelo_node_editor.h"

using namespace std;

#define PNE_GETTIME            chrono::system_clock::now()
#define PNE_GETTIEM_TIME_SIZE  chrono::duration_cast<chrono::milliseconds>(PNE_GETTIME.time_since_epoch()).count()
#define PNE_TIMESEED_SRAND     srand((uint32_t)PNE_GETTIEM_TIME_SIZE)

namespace PNEinit {

	void initialization_imgui(imguiinit initparam, GLFWwindow* wobj) {
        IMGUI_CHECKVERSION();

        // Setup ImGui Context.
        ImGui::CreateContext();
        ImGuiIO& GuiIO = ImGui::GetIO(); (void)GuiIO;

        // ����, �ֱ� ����.
        GuiIO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // enable keyboard controls.
        GuiIO.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // enable gamepad controls.

        // setup dear imgui style.
        ImGui::StyleColorsDark();
        // ImGui::StyleColorsLight();
        {
            ImGuiStyle* config_style = &ImGui::GetStyle();
            
            pne_system_style::style_preset_type(
                initparam.style_typenumber, // style type.
                config_style->Colors        // control draw colors.
            );
        }

        // init set fonts.
        auto SetFonts = ImGui::GetIO().Fonts;
        SetFonts->AddFontFromFileTTF
        (
            initparam.gui_fonts_path,
            initparam.gui_fonts_size,
            NULL,
            SetFonts->GetGlyphRangesChineseFull()
        );

        // setup platform & renderer backends.
        ImGui_ImplGlfw_InitForOpenGL(wobj, true);
        ImGui_ImplOpenGL3_Init(initparam.gui_shader_version);
	}

    void initialization_imnodes() {
        PNE_TIMESEED_SRAND; // time => srabnd seed.

        // setup ImNodes context.
        ImNodes::CreateContext();
        ImNodes::StyleColorsDark();
    }
}

namespace PNErender {
    
    void rendertick_gui(
        bool&            render_flag, 
        function<void()> render_gui
    ) {
        // start the Dear ImGui frame.
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // draw flag. 
        // render node state False: Not Draw&Compute.
        if (render_flag) 
        {
            pne_node_component::component_pcs_tick();
        }
        render_gui(); // draw imgui function.

        // render imgui.
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

namespace PNEclose {

    void close_imgui() {
        // End Close ImGui.
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void close_imnodes() {
        // Free Context.
        ImNodes::DestroyContext();
    }
}

extern vector<pne_node_component::node_attribute> __NODE_COMPONENTS;
extern vector<pne_node_component::node_attribute> __NODE_COMPONENTS_DCS;
extern unordered_map<int32_t, pne_node_component::node_link_line> __NODE_LINESLINK;

namespace PNEpreset {

    bool             window_no_close = false;
    ImGuiWindowFlags window_flags = NULL;

    // Ԥ��������.
    void component_guipanel() {
        static bool WindowNoMove = true;

        if (WindowNoMove) {
            window_flags  = ImGuiWindowFlags_NoMove;   // �̶�λ��.
            window_flags |= ImGuiWindowFlags_NoResize; // �̶���С.
            window_flags |= ImGuiWindowFlags_NoCollapse;
        }
        else
            window_flags = NULL;

        ImGui::Begin("Node Components List", &window_no_close, window_flags);
        {
            ImGui::Checkbox("Fixed Panel", &WindowNoMove);
            ImGui::Checkbox("Fixed Editor", &pne_node_component::editor_fixed_move);

            ImGui::Text("Render ImGui: %.2f fps", ImGui::GetIO().Framerate);
            ImGui::Text("");

            // Style FrameRounding.
            ImGui::GetStyle().FrameRounding = 7.2f;

            // Components List.
            for (auto __NODE_COMPONENT : __NODE_COMPONENTS) {
                // create components.
                if (ImGui::Button(__NODE_COMPONENT.node_title.c_str(), ImVec2(220.0f, 32.0f))) {
                    // create copy node_attribute.
                    pne_node_component::node_attribute create_node = __NODE_COMPONENT;

                    // ���� ������� ����Ψһ����.
                    pne_node_component::component_allocation(create_node);

                    // load => __NODE_COMPONENTS => __NODE_COMPONENTS_DCS
                    __NODE_COMPONENTS_DCS.push_back(create_node);
                }
            }

            ImGui::Text(u8"��������: %u lines", __NODE_LINESLINK.size());
            ImGui::Text(u8"�ڵ�����: %u nodes", __NODE_COMPONENTS_DCS.size());
        }
        ImGui::End();
    }

    bool component_load(StrText nodecmp_jsonpath) {
        bool rteurn_flag = true;

        // load config json => push component.
        __NODE_COMPONENTS.push_back(
            pne_node_configfile::load_component_json
            (
                nodecmp_jsonpath, 
                rteurn_flag
            )
        );
        return rteurn_flag;
    }
}

using namespace pne_node_component;
namespace pne_node_configfile {

    node_attribute load_component_json(StrText jsonpath, bool& state) {
        node_attribute return_node_cmp = {};

        ifstream read_jsonfile(jsonpath);
        if (!read_jsonfile) {

            // Failed read json.
            state = false;
        }
        else {

            // RapidJSON read json.
            string jsonString((std::istreambuf_iterator<char>(read_jsonfile)), std::istreambuf_iterator<char>());
            read_jsonfile.close();

            // ���� json string.
            rapidjson::Document jsondoc;
            jsondoc.Parse(jsonString.c_str());

            return_node_cmp.node_number = NULL;

            if (!jsondoc.HasParseError() && jsondoc.IsObject()) {
                
                // ���� node_color "node color" 
                if (jsondoc.HasMember("node color") && jsondoc["node color"].IsArray()) {

                    const auto& nodeColor = jsondoc["node color"];
                    
                    return_node_cmp.node_color.x = nodeColor[0].GetFloat();
                    return_node_cmp.node_color.y = nodeColor[1].GetFloat();
                    return_node_cmp.node_color.z = nodeColor[2].GetFloat();
                    return_node_cmp.node_color.w = nodeColor[3].GetFloat();
                }

                // ���� node_color_click "node color click"
                if (jsondoc.HasMember("node color click") && jsondoc["node color click"].IsArray()) {

                    const auto& nodeColorClick = jsondoc["node color click"];

                    return_node_cmp.node_color_click.x = nodeColorClick[0].GetFloat();
                    return_node_cmp.node_color_click.y = nodeColorClick[1].GetFloat();
                    return_node_cmp.node_color_click.z = nodeColorClick[2].GetFloat();
                    return_node_cmp.node_color_click.w = nodeColorClick[3].GetFloat();
                }

                // ���� node_title "node title"
                if (jsondoc.HasMember("node title") && jsondoc["node title"].IsObject()) {

                    const auto& nodeTitle = jsondoc["node title"];

                    if (nodeTitle.HasMember("text") && nodeTitle["text"].IsString()) {
                        
                        return_node_cmp.node_title = nodeTitle["text"].GetString();
                    }
                }

                // ���� in_point "input point"
                if (jsondoc.HasMember("input point") && jsondoc["input point"].IsArray()) {

                    const auto& inPoint = jsondoc["input point"].GetArray();

                    for (const auto& point : inPoint) {
                        node_in_connectpoint inConnectPoint;

                        inConnectPoint.point_number = NULL;

                        if (point.HasMember("point color") && point["point color"].IsArray()) {

                            const auto& pointColor = point["point color"].GetArray();

                            inConnectPoint.point_color.x = pointColor[0].GetFloat();
                            inConnectPoint.point_color.y = pointColor[1].GetFloat();
                            inConnectPoint.point_color.z = pointColor[2].GetFloat();
                            inConnectPoint.point_color.w = pointColor[3].GetFloat();
                        }

                        if (point.HasMember("point text") && point["point text"].IsObject()) {

                            const auto& pointText = point["point text"];

                            if (pointText.HasMember("text") && pointText["text"].IsString()) {

                                inConnectPoint.point_text = pointText["text"].GetString();
                            }
                        }

                        if (point.HasMember("point param") && point["point param"].IsInt()) {

                            const auto& pointType = point["point param"].GetInt();
                            inConnectPoint.point_param_type = (PARAMTYPE)pointType;
                        }
                        return_node_cmp.in_connect.push_back(inConnectPoint);
                    }
                }

                // ���� out_point "output point"
                if (jsondoc.HasMember("output point") && jsondoc["output point"].IsArray()) {

                    const auto& outPoint = jsondoc["output point"].GetArray();

                    for (const auto& point : outPoint) {
                        node_out_connectpoint outConnectPoint;

                        outConnectPoint.point_number = NULL;

                        if (point.HasMember("point color") && point["point color"].IsArray()) {

                            const auto& pointColor = point["point color"].GetArray();

                            outConnectPoint.point_color.x = pointColor[0].GetFloat();
                            outConnectPoint.point_color.y = pointColor[1].GetFloat();
                            outConnectPoint.point_color.z = pointColor[2].GetFloat();
                            outConnectPoint.point_color.w = pointColor[3].GetFloat();
                        }

                        if (point.HasMember("point text") && point["point text"].IsObject()) {

                            const auto& pointText = point["point text"];

                            if (pointText.HasMember("text") && pointText["text"].IsString()) {

                                outConnectPoint.point_text = pointText["text"].GetString();
                            }
                        }

                        if (point.HasMember("point param") && point["point param"].IsInt()) {

                            const auto& pointType = point["point param"].GetInt();
                            outConnectPoint.point_param_type = (PARAMTYPE)pointType;
                        }
                        return_node_cmp.out_connect.push_back(outConnectPoint);
                    }
                }

                // ���� node_numtype "node type"
                if (jsondoc.HasMember("node type") && jsondoc["node type"].IsUint()) {

                    return_node_cmp.node_numtype = jsondoc["node type"].GetUint();
                }
            }
            else
                state = false;
            state = true;
        }

        return return_node_cmp;
    }
}