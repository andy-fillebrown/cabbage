/*
  ==============================================================================

    CabbageOutpuConsoleComponent.h
    Created: 16 Oct 2016 3:33:16pm
    Author:  rory

  ==============================================================================
*/

#ifndef CABBAGEOUTPUCONSOLECOMPONENT_H_INCLUDED
#define CABBAGEOUTPUCONSOLECOMPONENT_H_INCLUDED

#include "CabbageIds.h"
#include "CabbageSettings.h"

class CabbageOutputConsole : public Component
{
    ScopedPointer<TextEditor> textEditor;
public:
    CabbageOutputConsole(ValueTree valueTree): Component(), value(valueTree)
    {
        addAndMakeVisible(textEditor = new TextEditor(), true);
        textEditor->setColour(Label::outlineColourId, Colours::white);
        textEditor->setColour(TextEditor::textColourId, CabbageSettings::getColourFromValueTree(valueTree, CabbageColourIds::consoletext, Colours::grey.darker()));
		textEditor->setColour(TextEditor::backgroundColourId, CabbageSettings::getColourFromValueTree(valueTree, CabbageColourIds::consolebackground, Colours::grey.darker()));
        textEditor->setMultiLine(true);
        textEditor->setReadOnly(true);
        textEditor->setFont(Font("Arial", 18, 0));


        String initString = (SystemStats::getOperatingSystemName() +
                             "CPU: " + String (SystemStats::getCpuSpeedInMegaherz())
                             + "MHz  Cores: " + String (SystemStats::getNumCpus())
                             + "  " + String (SystemStats::getMemorySizeInMegabytes()) + "MB");
        setText(initString);
    };

    ~CabbageOutputConsole() {};


    void setText(String text)
    {
        textEditor->insertTextAtCaret(text);
        textEditor->setCaretPosition(textEditor->getText().length());
    }

    String getText()
    {
        const MessageManagerLock lock;
        return textEditor->getText();
    }

	void updateColourScheme()
	{
        textEditor->setColour(TextEditor::textColourId, CabbageSettings::getColourFromValueTree(value, CabbageColourIds::consoletext, Colours::grey.darker()));
		textEditor->setColour(TextEditor::backgroundColourId, CabbageSettings::getColourFromValueTree(value, CabbageColourIds::consolebackground, Colours::grey.darker()));	
		repaint();	
	}

    void setFontSize(int size)
    {
        textEditor->setFont(Font("Arial", size, 0));
    }

    void resized()
    {
        Rectangle<int> area (getLocalBounds());
        textEditor->setBounds(area.reduced(4));
    }

    void paint(Graphics& g)
    {
        g.fillAll(Colours::grey);
//        g.setColour(Colours::white);
//        g.drawRoundedRectangle(getLocalBounds().toFloat(), 2, 2);
//        g.drawFittedText("Csound output", getLocalBounds().withHeight(18), Justification::centred, 1, 1.f);
    }

private:
	ValueTree value;

};



#endif  // CABBAGEOUTPUCONSOLECOMPONENT_H_INCLUDED
