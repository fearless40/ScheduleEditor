#include "pch.h"
#include "AppUI.h"

using namespace winrt::Windows::UI;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Media;

AppUI appui;

AppUI::AppUI()
{
}


AppUI::~AppUI()
{
}

void AppUI::initalize()
{
	Window window = Window::Current();

	mTop = StackPanel();
	mMiddle = StackPanel();
	mBottom = StackPanel();
	mContent = Grid();
	mStatusBar = TextBlock();

	RowDefinition row1, row2, row3;
	Thickness border{ 0,1,0,0 };

	row1.MaxHeight(100.0);
	row3.MaxHeight(25.0);
	
	mContent.RowDefinitions().Append(row1);
	mContent.RowDefinitions().Append(row2);
	mContent.RowDefinitions().Append(row3);

	mTop.MaxHeight(100);
	mBottom.MaxHeight(50);
	//mBottom.VerticalAlignment(VerticalAlignment::Center);
	mBottom.Background(SolidColorBrush(Colors::LightGray()));
	mBottom.BorderThickness(border);
	mBottom.BorderBrush(SolidColorBrush(Colors::Black()));

	mStatusBar.VerticalAlignment(VerticalAlignment::Center);

	mContent.Children().Append(mTop);
	mContent.Children().Append(mMiddle);
	mContent.Children().Append(mBottom);

	mContent.SetRow(mTop, 0);
	mContent.SetRow(mMiddle, 1);
	mContent.SetRow(mBottom, 2);

	mBottom.Orientation(Orientation::Horizontal);
	mBottom.Children().Append(mStatusBar);

	/*mStatusBar.FontFamily(FontFamily(L"Segoe UI Semibold"));
	mStatusBar.FontSize(72.0);
	//mStatusBar.Foreground(SolidColorBrush(Colors::Orange()));
	mStatusBar.VerticalAlignment(VerticalAlignment::Center);
	mStatusBar.TextAlignment(TextAlignment::Center);
	mStatusBar.TextWrapping(TextWrapping::Wrap);
	*/
	window.Content(mContent);

}

void AppUI::content_vert()
{
	mMiddle.Orientation(Orientation::Vertical);
}

void AppUI::content_horiz()
{
	mMiddle.Orientation(Orientation::Horizontal);
}

void AppUI::content_clear()
{
	mMiddle.Children().Clear();
}

void AppUI::content_set(winrt::Windows::UI::Xaml::FrameworkElement & const element)
{
	content_clear();
	mMiddle.Children().Append(element);
}

void AppUI::statusbar_set(std::wstring value)
{
	mStatusBar.Text(value);
}

void AppUI::statusbar_clear()
{
	mStatusBar.Text(L"");
}

AppUI & AppUI::get()
{
	return appui;
}
