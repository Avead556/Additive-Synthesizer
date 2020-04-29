// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple JUCE sine wave synthesizer

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Sine.h"

class MainContentComponent :
    public AudioAppComponent,
    private Slider::Listener,
    private ToggleButton::Listener
{
public:
    MainContentComponent() : gain (0.0), onOff (0), samplingRate(0.0)
    {
        nots["C"] = C;
        nots["D"] = D;
        nots["E"] = E;
        nots["F"] = F;
        nots["G"] = G;
        nots["A"] = A;
        nots["B"] = B;

        // button to add the "C" root note
        addAndMakeVisible(onNoteCButton);
        onNoteCButton.addListener(this);
        addAndMakeVisible(onNoteCButtonLabel);
        onNoteCButtonLabel.setText ("C", dontSendNotification);
        onNoteCButtonLabel.attachToComponent (&onNoteCButton, true);
  
        // button to add the "D" root note
        addAndMakeVisible(onNoteDButton);
        onNoteDButton.addListener(this);
        addAndMakeVisible(onNoteDButtonLabel);
        onNoteDButtonLabel.setText ("D", dontSendNotification);
        onNoteDButtonLabel.attachToComponent (&onNoteDButton, true);
        
        // button to add the "E" root note
        addAndMakeVisible(onNoteEButton);
        onNoteEButton.addListener(this);
        addAndMakeVisible(onNoteEButtonLabel);
        onNoteEButtonLabel.setText ("E", dontSendNotification);
        onNoteEButtonLabel.attachToComponent (&onNoteEButton, true);

        // button to add the "F" root note
        addAndMakeVisible(onNoteFButton);
        onNoteFButton.addListener(this);
        addAndMakeVisible(onNoteFButtonLabel);
        onNoteFButtonLabel.setText ("F", dontSendNotification);
        onNoteFButtonLabel.attachToComponent (&onNoteFButton, true);
        
        // button to add the "G" root note
        addAndMakeVisible(onNoteGButton);
        onNoteGButton.addListener(this);
        addAndMakeVisible(onNoteGButtonLabel);
        onNoteGButtonLabel.setText ("G", dontSendNotification);
        onNoteGButtonLabel.attachToComponent (&onNoteGButton, true);

        // button to add the "A" root note
        addAndMakeVisible(onNoteAButton);
        onNoteAButton.addListener(this);
        addAndMakeVisible(onNoteAButtonLabel);
        onNoteAButtonLabel.setText ("A", dontSendNotification);
        onNoteAButtonLabel.attachToComponent (&onNoteAButton, true);

        // button to add the "B" root note
        addAndMakeVisible(onNoteBButton);
        onNoteBButton.addListener(this);
        addAndMakeVisible(onNoteBButtonLabel);
        onNoteBButtonLabel.setText ("B", dontSendNotification);
        onNoteBButtonLabel.attachToComponent (&onNoteBButton, true);
        
        // configuring frequency slider and adding it to the main window
        addAndMakeVisible (frequencySlider);
        frequencySlider.setRange (50.0, 5000.0);
        frequencySlider.setSkewFactorFromMidPoint (500.0);
        frequencySlider.setValue(1000); // will also set the default frequency of the sine osc
        frequencySlider.addListener (this);
        
        // configuring frequency label box and adding it to the main window
        addAndMakeVisible(frequencyLabel);
        frequencyLabel.setText ("Frequency", dontSendNotification);
        frequencyLabel.attachToComponent (&frequencySlider, true);
        
        
        // configuring gain slider and adding it to the main window
        addAndMakeVisible (gainSlider);
        gainSlider.setRange (0.0, 1.0);
        gainSlider.setValue(0.5); // will alsi set the default gain of the sine osc
        gainSlider.addListener (this);
        
        
        // configuring gain label and adding it to the main window
        addAndMakeVisible(gainLabel);
        gainLabel.setText ("Gain", dontSendNotification);
        gainLabel.attachToComponent (&gainSlider, true);
        
        
        // configuring on/off button and adding it to the main window
        addAndMakeVisible(onOffButton);
        onOffButton.addListener(this);
        
        
        // configuring on/off label and adding it to the main window
        addAndMakeVisible(onOffLabel);
        onOffLabel.setText ("On/Off", dontSendNotification);
        onOffLabel.attachToComponent (&onOffButton, true);

        setSize (600, 130);
        nChans = 1;
        setAudioChannels (0, nChans); // no inputs, one output
 
    }
    
    ~MainContentComponent()
    {
        shutdownAudio();
    }
    
    void resized() override
    {
        // placing the UI elements in the main window
        // getWidth has to be used in case the window is resized by the user
        const int sliderLeft = 80;
       
       // frequencySlider.setBounds (sliderLeft, 10, getWidth() - sliderLeft - 20, 20);
        gainSlider.setBounds (sliderLeft, 10, getWidth() - sliderLeft - 20, 20);
        onOffButton.setBounds (sliderLeft, 40, getWidth() - sliderLeft - 20, 20);
        
        onNoteCButton.setBounds (sliderLeft, 60, 25, 20);
        onNoteDButton.setBounds (2*sliderLeft, 60, 25, 20);
        onNoteFButton.setBounds (3*sliderLeft, 60, 25, 20);
        onNoteEButton.setBounds (4*sliderLeft, 60, 25, 20);
        onNoteAButton.setBounds (5*sliderLeft, 60, 25, 20);
        onNoteGButton.setBounds (6*sliderLeft, 60, 25, 20);
        onNoteBButton.setBounds (7*sliderLeft, 60, 25, 20);
    }
    
    void sliderValueChanged (Slider* slider) override
    {
        if (samplingRate > 0.0){
            if (slider == &gainSlider){
                gain = gainSlider.getValue();
            }
        }
    }
    
    void buttonClicked (Button* button) override
    {
        // turns audio on or off
        if(button == &onOffButton){

            if(onOffButton.getToggleState()){
               onOff = 1;
            }else{
               onOff = 0;
            }

        }
        
        
       if(button == &onNoteCButton){

            if(onNoteCButton.getToggleState()){
               addNoteToSins(0, "C");
            }else{
               deleteNoteToSins(0);
            }

        }
        
        if(button == &onNoteDButton){

           if(onNoteDButton.getToggleState()){
               addNoteToSins(1, "D");
           }else{
               deleteNoteToSins(1);
           }

        }
        
        if(button == &onNoteEButton){

           if(onNoteEButton.getToggleState()){
               addNoteToSins(2, "E");
           }else{
               deleteNoteToSins(2);
           }

        }
        
        if(button == &onNoteFButton){

           if(onNoteFButton.getToggleState()){
               addNoteToSins(3, "F");
           }else{
               deleteNoteToSins(3);
           }

        }
        
        if(button == &onNoteGButton){

           if(onNoteGButton.getToggleState()){
               addNoteToSins(4, "G");
           }else{
               deleteNoteToSins(4);
           }

        }
        
       if(button == &onNoteAButton){

           if(onNoteAButton.getToggleState()){
               addNoteToSins(5, "A");
           }else{
               deleteNoteToSins(5);
           }

        }
        
       if(button == &onNoteBButton){

           if(onNoteBButton.getToggleState()){
               addNoteToSins(6, "B");
           }else{
               deleteNoteToSins(6);
           }

        }
        
    }
    
    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
    {
        samplingRate = sampleRate;
  
        for (int i = 0; i <= sinsQiuantity-1; i++){
            sines_list.push_back(new Sine());
            sines_list[i]->setSamplingRate(sampleRate);
            sines_list[i]->setFrequency(0.0);
        }
        

    }   
    
    void releaseResources() override
    {

    }
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        // getting the audio output buffer to be filled
        float* const buffer = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
        float sumSample = 0.0000;
        /*
        there is noise when sumuping sines  
        for (int i=0; i<=sines_list.size()-1; i++) {
            sumSample += sines_list[i]->tick();
        }
        */

         
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            
            if(onOff == 1){
                //  buffer[sample] =sumSample * gain;
       
               buffer[sample] = (sines_list[0]->tick() + sines_list[1]->tick() + sines_list[2]->tick() + sines_list[3]->tick() + sines_list[4]->tick() + sines_list[5]->tick() + sines_list[6]->tick())* gain;
            }else{
                buffer[sample] = 0.0;
            }
        }

    }
    
    void addNoteToSins(int i, std::string key){
        
        if(i<=sines_list.size()){
              sines_list[i]->setFrequency(nots[key]);
        }
        
      
   
    }
    
    void deleteNoteToSins(int i){
        
         if(i<=sines_list.size()){
            sines_list[i]->setFrequency(0.0);
        }
       
    }
    
private:
    // UI Elements
    Slider frequencySlider;
    Slider gainSlider;

    ToggleButton onOffButton;
    ToggleButton onNoteCButton;
    ToggleButton onNoteDButton;
    ToggleButton onNoteEButton;
    ToggleButton onNoteFButton;
    ToggleButton onNoteGButton;
    ToggleButton onNoteAButton;
    ToggleButton onNoteBButton;

    Label frequencyLabel, gainLabel, onOffLabel,onNoteCButtonLabel,onNoteDButtonLabel;
    Label onNoteEButtonLabel;
    Label onNoteFButtonLabel;
    Label onNoteGButtonLabel;
    Label onNoteAButtonLabel;
    Label onNoteBButtonLabel;
   
    
    // Global Variables
    int sinsQiuantity = 7;
    std::vector<Sine *> sines_list;
    std::map<std::string, double > nots;

    float gain;
    int onOff, samplingRate, nChans;
    
    const double C = 500.00;
    const double D = 650.00;
    const double E = 750.00;
    const double F = 850.00;
    const double G = 950.50;
    const double A = 1050.50;
    const double B = 1150.87;    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
