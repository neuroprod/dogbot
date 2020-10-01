#include "PID.h"

#include "cinder/CinderImGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;
float PID::calculate(float target, float current) 
{
    if (inv)current *= -1;
	// Calculate error
	error = target - current;

	// Proportional term
	 Pout = Kp * error;

	// Integral term
	integral += error * dt;
	if(integral>maxI)integral=maxI;
    if(integral<minI)integral=minI;
	Iout = Ki * integral;

	derivative = (error - pre_error)/dt ;
	 Dout = 0;
	 Dout = Kd * derivative;


	// Calculate total output
	 output = Pout + Iout + Dout;

	// Restrict to max/min
	if (output > max)
		output = max;
	else if (output < min)
		output = min;

	// Save error to previous error
	pre_error = error;

	
	return output;


}
void PID::reset(){
    pre_error =0;
    integral=0;
}
void PID::drawGui(string name)
{
	ImGui::PushID(name.c_str());
    ImGui::Text("%s error=%f",name.c_str() ,error);
    ImGui::Text("integral =%f derivative =%f",integral,derivative);
    ImGui::Text("P=%f I=%f  D=%f  out=%f",Pout,Iout,Dout,output);
    ImGui::DragFloat("p", &Kp, 0.1f, -2.f, 10.f);
    ImGui::DragFloat("i", &Ki, 0.001f, 0, 1);
    ImGui::DragFloat("d", &Kd, 0.001f, 0, 1);
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