#include "PID.h"

#include "cinder/CinderImGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;
float PID::calculate(float target, float current) 
{
	
	// Calculate error
	error = target - current;

	// Proportional term
	float Pout = Kp * error;

	// Integral term
	integral -= error * dt*50.0;
	float Iout = Ki * integral;
	//if (Iout < 0 && Pout>0)Iout = 0;
	//if (Iout > 0 && Pout<0)Iout = 0;
	// Derivative term
	float derivative = (error - pre_error) ;
	float Dout = 0;
	 Dout = Kd * -derivative;


	// Calculate total output
	 output = Pout + Iout + Dout;

	// Restrict to max/min
	if (output > max)
		output = max;
	else if (output < min)
		output = min;

	// Save error to previous error
	pre_error = error;
	if (inv)output *= -1;
	
	return output;


}
void PID::drawGui(string name)
{
	ImGui::PushID(name.c_str());
    ImGui::Text("%s error=%f",name.c_str() ,error/3.1415f*180.f);
    ImGui::Text("integral =%f output =%f ",integral,output);
    ImGui::DragFloat("p", &Kp, 1.0f, 0, 2000);
    ImGui::DragFloat("i", &Ki, 0.1f, 0, 1000);
    ImGui::DragFloat("d", &Kd, 0.1f, 0, 1000);
    ImGui::Checkbox("invert", &inv);
	/*float errorSum = 0;
	{
		errors.push_back(error);
		if (errors.size() > 500) errors.erase(errors.begin());

		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return;
		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(500, 100));
		const ImRect inner_bb(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding);
		const ImRect total_bb(frame_bb.Min, frame_bb.Max);
		ImGui::ItemSize(total_bb, style.FramePadding.y);
		if (!ImGui::ItemAdd(total_bb, 0, &frame_bb))
			return;
		ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);

		const ImU32 col_base = ImGui::GetColorU32(ImGuiCol_CheckMark);

		for (int i = 0; i < errors.size()-1; i++) {
			errorSum += abs(errors[i]);
			float error1 = errors[i]*8.f;
			float error2 = errors[i+1]*8.f;
			ImVec2 tp0 = ImVec2(0.002f*i, 0.5f+error1);
			ImVec2 tp1 = ImVec2(0.002f*i,0.5f + error2);
			ImVec2 pos0 = ImLerp(inner_bb.Min, inner_bb.Max, tp0);
			ImVec2 pos1 = ImLerp(inner_bb.Min, inner_bb.Max, tp1);

			window->DrawList->AddLine(pos0, pos1, col_base);
		}
	}
	string e = to_string(errorSum);
    ImGui::Text(e.c_str());*/
    ImGui::PopID();
}