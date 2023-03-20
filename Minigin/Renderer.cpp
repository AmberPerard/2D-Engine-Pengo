#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"

#include <imgui.h>
#include <imgui_plot.h>
#include <backends/imgui_impl_opengl2.h>
#include <backends/imgui_impl_sdl2.h>

#include "TrashTheCache.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}


	// Init IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();

	m_pTrashTheCache = new TrashTheCache();
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();


	//ImGui
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();

	//this should loop over the scene
	Exercise1();
	Exercise2();
	//

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	//trash
	delete m_pTrashTheCache;
	m_pTrashTheCache = nullptr;

	// ImGui
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	// Renderer
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }

//move to component
void dae::Renderer::Exercise1() const
{
	bool my_tool_active{};
	static bool clickedButton{};
	static bool isCalculated{};
	ImGui::Begin("Exercise1", &my_tool_active, ImGuiWindowFlags_AlwaysAutoResize);

	static int i0 = 10;
	ImGui::InputInt("# Samples", &i0);

	ImGui::PlotConfig conf;
	conf.scale.min = 0;
	conf.tooltip.show = true;
	conf.tooltip.format = "Stepsize:%.0f\nValue: %.0f";
	conf.grid_x.show = false;
	conf.grid_y.show = false;
	conf.frame_size = ImVec2(250, 100);
	conf.line_thickness = 2.0f;

	if (ImGui::Button("Trash the Cache"))
	{
		clickedButton = true;
	}

	if (clickedButton)
	{
		ImGui::Text("Wait for it...");
		m_pTrashTheCache->FirstExercise(i0);
		isCalculated = true;
		clickedButton = false;
	}
	if(isCalculated)
	{
		conf.values.color = ImColor(255, 150, 0);
		conf.values.xs = m_pTrashTheCache->GetExercise1XData()->data();
		conf.values.ys = m_pTrashTheCache->GetExercise1YData()->data();
		conf.values.count = static_cast<int>(m_pTrashTheCache->GetExercise1XData()->size());
		conf.scale.max = 1024;
		ImGui::Plot("Exercise01", conf);
	}

	ImGui::End();
}

//move the component
void dae::Renderer::Exercise2() const
{
	bool my_tool_active;
	static bool clickedButtonNormal{};
	static bool isCalculatingNormal{};
	static bool clickedButtonAlt{};
	static bool isCalculatingAlt{};

	ImGui::PlotConfig conf;
	conf.scale.min = 0;
	conf.tooltip.show = true;
	conf.tooltip.format = "Stepsize:%.0f\nValue: %.0f";
	conf.grid_x.show = false;
	conf.grid_y.show = false;
	conf.frame_size = ImVec2(250, 100);
	conf.line_thickness = 2.0f;

	ImGui::Begin("Exercise2", &my_tool_active, ImGuiWindowFlags_AlwaysAutoResize);

	static int i0 = 100;
	ImGui::InputInt("# Samples", &i0);
	if (ImGui::Button("Trash the Cache with GameObject3D"))
	{
		clickedButtonNormal = true;
	}
	if (clickedButtonNormal)
	{
		ImGui::Text("Wait for it...");
		m_pTrashTheCache->SecondExercise(i0);
		isCalculatingNormal = true;
		clickedButtonNormal = false;
	}
	if (isCalculatingNormal)
	{
		conf.values.color = ImColor(255, 150, 0);
		conf.values.xs = m_pTrashTheCache->GetExercise2XData()->data();
		conf.values.ys = m_pTrashTheCache->GetExercise2YData()->data();
		conf.values.count = static_cast<int>(m_pTrashTheCache->GetExercise2XData()->size());
		conf.scale.max = 1024;
		ImGui::Plot("Exercise02 Normal", conf);
	}
	if (ImGui::Button("Trash the Cache with GameObject3DAlt"))
	{
		clickedButtonAlt = true;
		m_pTrashTheCache->SecondExerciseALT(i0);
		isCalculatingAlt = true;
		clickedButtonAlt = false;
	}
	if (clickedButtonAlt)
	{
		ImGui::Text("Wait for it...");
	}
	if(isCalculatingAlt)
	{
		conf.values.color = ImColor(255, 150, 0);
		conf.values.xs = m_pTrashTheCache->GetExercise2AltXData()->data();
		conf.values.ys = m_pTrashTheCache->GetExercise2AltYData()->data();
		conf.values.count = static_cast<int>(m_pTrashTheCache->GetExercise2AltXData()->size());
		conf.scale.max = 1024;
		ImGui::Plot("Exercise02 Alt", conf);
	}


	if(isCalculatingAlt && isCalculatingNormal)
	{
		static const float* y_data[] = { m_pTrashTheCache->GetExercise2YData()->data(), m_pTrashTheCache->GetExercise2AltYData()->data() };
		static ImU32 colors[2] = { ImColor(50, 255, 50), ImColor(50, 50, 255) };

		ImGui::Text("Combined:");
		conf.values.xs = m_pTrashTheCache->GetExercise2AltXData()->data();
		conf.values.count = static_cast<int>(m_pTrashTheCache->GetExercise2AltXData()->size());
		conf.values.ys = nullptr; // Clear data
		conf.values.ys_list = y_data;
		conf.values.ys_count = 2;
		conf.values.colors = colors;

		conf.scale.max = 1024;
		ImGui::Plot("Extra", conf);
	}

	ImGui::End();
}
