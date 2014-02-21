/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#ifndef TOUCHKEYS_NO_GUI
#include "MappingListComponent.h"
//[/Headers]

#include "MappingListItem.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MappingListItem::MappingListItem (MappingListComponent& listComponent)
    : factory_(0), listComponent_(listComponent)
{
    addAndMakeVisible (bypassToggleButton = new ToggleButton ("Bypass toggle button"));
    bypassToggleButton->setButtonText ("Bypass");
    bypassToggleButton->addListener (this);

    addAndMakeVisible (showDetailsButton = new TextButton ("Show details button"));
    showDetailsButton->setButtonText ("Details...");
    showDetailsButton->addListener (this);

    addAndMakeVisible (mappingTypeLabel = new Label ("mapping type label",
                                                     "MappingType"));
    mappingTypeLabel->setFont (Font (18.00f, Font::plain));
    mappingTypeLabel->setJustificationType (Justification::centred);
    mappingTypeLabel->setEditable (false, false, false);
    mappingTypeLabel->setColour (TextEditor::textColourId, Colours::black);
    mappingTypeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (mappingShortEditorComponent = new MappingEditorComponent());
    mappingShortEditorComponent->setName ("mapping short editor component");

    addAndMakeVisible (noSettingsLabel = new Label ("no settings label",
                                                    "(no settings)"));
    noSettingsLabel->setFont (Font (15.00f, Font::plain));
    noSettingsLabel->setJustificationType (Justification::centred);
    noSettingsLabel->setEditable (false, false, false);
    noSettingsLabel->setColour (TextEditor::textColourId, Colours::black);
    noSettingsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (deleteButton = new TextButton ("delete button"));
    deleteButton->setButtonText ("Delete...");
    deleteButton->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (544, 72);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MappingListItem::~MappingListItem()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    bypassToggleButton = nullptr;
    showDetailsButton = nullptr;
    mappingTypeLabel = nullptr;
    mappingShortEditorComponent = nullptr;
    noSettingsLabel = nullptr;
    deleteButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MappingListItem::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colour (0xffa52a60));
    g.fillPath (internalPath1);
    g.setColour (Colours::black);
    g.strokePath (internalPath1, PathStrokeType (1.000f));

    g.setColour (Colour (0xffa52a94));
    g.fillPath (internalPath2);
    g.setColour (Colours::black);
    g.strokePath (internalPath2, PathStrokeType (0.500f));

    //[UserPaint] Add your own custom painting code here..
    /*MappingListComponent *parent = static_cast<MappingListComponent*>(getParentComponent());
    if(parent->isComponentSelected(this)) {
        g.setColour (Colours::lightblue);
        g.drawRect (0, 0, 544, 72, 5);
    }*/
    //[/UserPaint]
}

void MappingListItem::resized()
{
    bypassToggleButton->setBounds (24, 44, 72, 24);
    showDetailsButton->setBounds (456, 8, 80, 24);
    mappingTypeLabel->setBounds (8, 4, 104, 40);
    mappingShortEditorComponent->setBounds (120, 0, 328, 71);
    noSettingsLabel->setBounds (208, 24, 150, 24);
    deleteButton->setBounds (456, 44, 80, 20);
    internalPath1.clear();
    internalPath1.startNewSubPath (544.0f, 72.0f);
    internalPath1.lineTo (0.0f, 72.0f);
    internalPath1.closeSubPath();

    internalPath2.clear();
    internalPath2.startNewSubPath (119.0f, 16.0f);
    internalPath2.lineTo (119.0f, 56.0f);
    internalPath2.closeSubPath();

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MappingListItem::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    if(factory_ == 0)
        return;
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == bypassToggleButton)
    {
        //[UserButtonCode_bypassToggleButton] -- add your button handler code here..
        bool bypass = bypassToggleButton->getToggleState();
        factory_->setBypassed(bypass);
        //[/UserButtonCode_bypassToggleButton]
    }
    else if (buttonThatWasClicked == showDetailsButton)
    {
        //[UserButtonCode_showDetailsButton] -- add your button handler code here..
        //[/UserButtonCode_showDetailsButton]
    }
    else if (buttonThatWasClicked == deleteButton)
    {
        //[UserButtonCode_deleteButton] -- add your button handler code here..
        // Display an alert to confirm the user wants to delete this mapping
        AlertWindow::showOkCancelBox (AlertWindow::QuestionIcon,
                                      "Delete mapping",
                                      "Are you sure you want to delete this mapping?",
                                      String::empty,
                                      String::empty,
                                      0,
                                      ModalCallbackFunction::forComponent (alertBoxResultChosen, this));
        //[/UserButtonCode_deleteButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

// Called when user clicks a result in the alert box to confirm deletion
void MappingListItem::alertBoxResultChosen(int result, MappingListItem *item)
{
    if(result != 0) {
        item->deleteMapping();
    }
}

// Delete this mapping factory
void MappingListItem::deleteMapping()
{
    listComponent_.deleteMapping(factory_);
}

// Set the mapping factory and create any editor components it uses
void MappingListItem::setMappingFactory(MappingFactory *factory)
{
    factory_ = factory;

    if(factory_->hasBasicEditor()) {
        // Has a short editor: make one and add it to the window, using the same bounds
        // as before
        const juce::Rectangle<int>& bounds = mappingShortEditorComponent->getBounds();
        mappingShortEditorComponent = factory_->createBasicEditor();
        addAndMakeVisible(mappingShortEditorComponent);
        mappingShortEditorComponent->setBounds(bounds);
        noSettingsLabel->setVisible(false);
    }
    else {
        noSettingsLabel->setVisible(true);
        mappingShortEditorComponent->setVisible(false);
    }

    if(factory_->hasExtendedEditor()) {
        // Has an extended editor: make one and keep it around for adding to a new window
        mappingLongEditorComponent = factory_->createExtendedEditor();
        showDetailsButton->setEnabled(true);
    }
    else {
        mappingLongEditorComponent = nullptr;
        showDetailsButton->setEnabled(false);
    }

    synchronize();
}

void MappingListItem::synchronize()
{
    if(factory_ == 0)
        return;

    // Update the label and the bypass button
    mappingTypeLabel->setText(factory_->factoryTypeName().c_str(), dontSendNotification);
    if(factory_->bypassed() != MappingFactory::kBypassOff)
        bypassToggleButton->setToggleState(true, dontSendNotification);
    else
        bypassToggleButton->setToggleState(false, dontSendNotification);

    // Update the short and long components if present
    if(mappingShortEditorComponent != 0)
        mappingShortEditorComponent->synchronize();
    if(mappingLongEditorComponent != 0)
        mappingLongEditorComponent->synchronize();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MappingListItem" componentName=""
                 parentClasses="public Component" constructorParams="MappingListComponent&amp; listComponent"
                 variableInitialisers="factory_(0), listComponent_(listComponent)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="544" initialHeight="72">
  <BACKGROUND backgroundColour="ffffffff">
    <PATH pos="0 0 100 100" fill="solid: ffa52a60" hasStroke="1" stroke="1, mitered, butt"
          strokeColour="solid: ff000000" nonZeroWinding="1">s 544 72 l 0 72 x</PATH>
    <PATH pos="0 0 100 100" fill="solid: ffa52a94" hasStroke="1" stroke="0.5, mitered, butt"
          strokeColour="solid: ff000000" nonZeroWinding="1">s 119 16 l 119 56 x</PATH>
  </BACKGROUND>
  <TOGGLEBUTTON name="Bypass toggle button" id="cfe71c39a64f4704" memberName="bypassToggleButton"
                virtualName="" explicitFocusOrder="0" pos="24 44 72 24" buttonText="Bypass"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTBUTTON name="Show details button" id="17ac5d15223ada90" memberName="showDetailsButton"
              virtualName="" explicitFocusOrder="0" pos="456 8 80 24" buttonText="Details..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="mapping type label" id="58b75e1d781dd4c6" memberName="mappingTypeLabel"
         virtualName="" explicitFocusOrder="0" pos="8 4 104 40" edTextCol="ff000000"
         edBkgCol="0" labelText="MappingType" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="18" bold="0" italic="0" justification="36"/>
  <GENERICCOMPONENT name="mapping short editor component" id="8cbc2e53072fcaa7" memberName="mappingShortEditorComponent"
                    virtualName="" explicitFocusOrder="0" pos="120 0 328 71" class="MappingEditorComponent"
                    params=""/>
  <LABEL name="no settings label" id="a8fb2694ebf4280b" memberName="noSettingsLabel"
         virtualName="" explicitFocusOrder="0" pos="208 24 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="(no settings)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="delete button" id="fced502f19d4fe5b" memberName="deleteButton"
              virtualName="" explicitFocusOrder="0" pos="456 44 80 20" buttonText="Delete..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
#endif // TOUCHKEYS_NO_GUI
//[/EndFile]
