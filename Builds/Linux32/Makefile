# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_BCF8FE09=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../juce/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0 -m32
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt -L/usr/lib/i386-linux-gnu -L/usr/lib/i386-linux-gnu/mesa -m32 /usr/local/lib/liblo32.a
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_BCF8FE09=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../juce/modules
  TARGET := TouchKeys
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_BCF8FE09=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../juce/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os -m32
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt -L/usr/lib/i386-linux-gnu -L/usr/lib/i386-linux-gnu/mesa -m32 /usr/local/lib/liblo32.a
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_BCF8FE09=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../juce/modules
  TARGET := TouchKeys
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
  $(OBJDIR)/MainWindow_ca618186.o \
  $(OBJDIR)/KeyboardZoneComponent_fd0d7a77.o \
  $(OBJDIR)/ControlWindowMainComponent_c67f9014.o \
  $(OBJDIR)/MappingListComponent_402cf84e.o \
  $(OBJDIR)/MappingListItem_7a9eebac.o \
  $(OBJDIR)/TouchkeyVibratoMappingShortEditor_27ad15dd.o \
  $(OBJDIR)/TouchkeyVibratoMapping_ea5c5156.o \
  $(OBJDIR)/TouchkeyVibratoMappingFactory_f90040de.o \
  $(OBJDIR)/TouchkeyReleaseAngleMapping_170b0b0a.o \
  $(OBJDIR)/TouchkeyReleaseAngleMappingFactory_9052f4aa.o \
  $(OBJDIR)/TouchkeyPitchBendMappingShortEditor_6afc649d.o \
  $(OBJDIR)/TouchkeyPitchBendMapping_78aba96.o \
  $(OBJDIR)/TouchkeyPitchBendMappingFactory_9fc4ef9e.o \
  $(OBJDIR)/TouchkeyOnsetAngleMapping_a77ca3ca.o \
  $(OBJDIR)/TouchkeyOnsetAngleMappingFactory_6a4803ea.o \
  $(OBJDIR)/TouchkeyMultiFingerTriggerMapping_f7bfe8a.o \
  $(OBJDIR)/TouchkeyMultiFingerTriggerMappingFactory_e811112a.o \
  $(OBJDIR)/TouchkeyKeyDivisionMapping_cea38eb0.o \
  $(OBJDIR)/TouchkeyKeyDivisionMappingFactory_33b42a44.o \
  $(OBJDIR)/TouchkeyControlMappingShortEditor_993f27a5.o \
  $(OBJDIR)/TouchkeyControlMapping_1e638c8e.o \
  $(OBJDIR)/TouchkeyControlMappingFactory_1db276a6.o \
  $(OBJDIR)/MappingScheduler_3b3284f8.o \
  $(OBJDIR)/TouchkeyBaseMapping_d96a411c.o \
  $(OBJDIR)/Mapping_57653e8d.o \
  $(OBJDIR)/MappingFactorySplitter_9525552e.o \
  $(OBJDIR)/MIDIKeyPositionMapping_750093d2.o \
  $(OBJDIR)/MRPMapping_742529ce.o \
  $(OBJDIR)/KeyboardDisplay_d9f334cf.o \
  $(OBJDIR)/KeyPositionGraphDisplay_5606e2d0.o \
  $(OBJDIR)/RawSensorDisplay_f15a0e36.o \
  $(OBJDIR)/IIRFilter_c9874248.o \
  $(OBJDIR)/Scheduler_5d9eed19.o \
  $(OBJDIR)/TimerNode_477a3545.o \
  $(OBJDIR)/TimestampSynchronizer_df7831b6.o \
  $(OBJDIR)/Trigger_66a771d6.o \
  $(OBJDIR)/TouchkeyOscEmulator_9ad15559.o \
  $(OBJDIR)/MidiKeyboardSegment_e1be9d70.o \
  $(OBJDIR)/KeyIdleDetector_2efa023e.o \
  $(OBJDIR)/KeyPositionTracker_4c4c0dd5.o \
  $(OBJDIR)/LogPlayback_1debad04.o \
  $(OBJDIR)/MidiInputController_1864322a.o \
  $(OBJDIR)/MidiOutputController_a68d4623.o \
  $(OBJDIR)/Osc_433b9284.o \
  $(OBJDIR)/OscMidiConverter_75608f25.o \
  $(OBJDIR)/PianoKey_1afca9bb.o \
  $(OBJDIR)/PianoKeyboard_f097ab55.o \
  $(OBJDIR)/PianoKeyCalibrator_6932659c.o \
  $(OBJDIR)/PianoPedal_34544d96.o \
  $(OBJDIR)/TouchkeyDevice_be3b7a9b.o \
  $(OBJDIR)/MainApplicationController_90b344b4.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_audio_basics_5460bccb.o \
  $(OBJDIR)/juce_audio_devices_44d00ac9.o \
  $(OBJDIR)/juce_audio_formats_73515469.o \
  $(OBJDIR)/juce_core_5f5a3bad.o \
  $(OBJDIR)/juce_data_structures_7e517fa9.o \
  $(OBJDIR)/juce_events_88dd09a1.o \
  $(OBJDIR)/juce_graphics_29b23085.o \
  $(OBJDIR)/juce_gui_basics_a9efcd81.o \
  $(OBJDIR)/juce_gui_extra_a9396b49.o \
  $(OBJDIR)/juce_opengl_492531cd.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking TouchKeys
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning TouchKeys
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)/*
	-@rm -rf $(OBJDIR)

strip:
	@echo Stripping TouchKeys
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/MainWindow_ca618186.o: ../../Source/GUI/MainWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/KeyboardZoneComponent_fd0d7a77.o: ../../Source/GUI/KeyboardZoneComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling KeyboardZoneComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ControlWindowMainComponent_c67f9014.o: ../../Source/GUI/ControlWindowMainComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ControlWindowMainComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MappingListComponent_402cf84e.o: ../../Source/GUI/MappingListComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MappingListComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MappingListItem_7a9eebac.o: ../../Source/GUI/MappingListItem.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MappingListItem.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyVibratoMappingShortEditor_27ad15dd.o: ../../Source/Mappings/Vibrato/TouchkeyVibratoMappingShortEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyVibratoMappingShortEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyVibratoMapping_ea5c5156.o: ../../Source/Mappings/Vibrato/TouchkeyVibratoMapping.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyVibratoMapping.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyVibratoMappingFactory_f90040de.o: ../../Source/Mappings/Vibrato/TouchkeyVibratoMappingFactory.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyVibratoMappingFactory.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyReleaseAngleMapping_170b0b0a.o: ../../Source/Mappings/ReleaseAngle/TouchkeyReleaseAngleMapping.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyReleaseAngleMapping.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyReleaseAngleMappingFactory_9052f4aa.o: ../../Source/Mappings/ReleaseAngle/TouchkeyReleaseAngleMappingFactory.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyReleaseAngleMappingFactory.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyPitchBendMappingShortEditor_6afc649d.o: ../../Source/Mappings/PitchBend/TouchkeyPitchBendMappingShortEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyPitchBendMappingShortEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyPitchBendMapping_78aba96.o: ../../Source/Mappings/PitchBend/TouchkeyPitchBendMapping.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyPitchBendMapping.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyPitchBendMappingFactory_9fc4ef9e.o: ../../Source/Mappings/PitchBend/TouchkeyPitchBendMappingFactory.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyPitchBendMappingFactory.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyOnsetAngleMapping_a77ca3ca.o: ../../Source/Mappings/OnsetAngle/TouchkeyOnsetAngleMapping.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyOnsetAngleMapping.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyOnsetAngleMappingFactory_6a4803ea.o: ../../Source/Mappings/OnsetAngle/TouchkeyOnsetAngleMappingFactory.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyOnsetAngleMappingFactory.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyMultiFingerTriggerMapping_f7bfe8a.o: ../../Source/Mappings/MultiFingerTrigger/TouchkeyMultiFingerTriggerMapping.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyMultiFingerTriggerMapping.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyMultiFingerTriggerMappingFactory_e811112a.o: ../../Source/Mappings/MultiFingerTrigger/TouchkeyMultiFingerTriggerMappingFactory.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyMultiFingerTriggerMappingFactory.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyKeyDivisionMapping_cea38eb0.o: ../../Source/Mappings/KeyDivision/TouchkeyKeyDivisionMapping.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyKeyDivisionMapping.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyKeyDivisionMappingFactory_33b42a44.o: ../../Source/Mappings/KeyDivision/TouchkeyKeyDivisionMappingFactory.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyKeyDivisionMappingFactory.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyControlMappingShortEditor_993f27a5.o: ../../Source/Mappings/Control/TouchkeyControlMappingShortEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyControlMappingShortEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyControlMapping_1e638c8e.o: ../../Source/Mappings/Control/TouchkeyControlMapping.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyControlMapping.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyControlMappingFactory_1db276a6.o: ../../Source/Mappings/Control/TouchkeyControlMappingFactory.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyControlMappingFactory.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MappingScheduler_3b3284f8.o: ../../Source/Mappings/MappingScheduler.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MappingScheduler.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyBaseMapping_d96a411c.o: ../../Source/Mappings/TouchkeyBaseMapping.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyBaseMapping.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Mapping_57653e8d.o: ../../Source/Mappings/Mapping.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Mapping.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MappingFactorySplitter_9525552e.o: ../../Source/Mappings/MappingFactorySplitter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MappingFactorySplitter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MIDIKeyPositionMapping_750093d2.o: ../../Source/Mappings/MIDIKeyPositionMapping.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MIDIKeyPositionMapping.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MRPMapping_742529ce.o: ../../Source/Mappings/MRPMapping.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MRPMapping.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/KeyboardDisplay_d9f334cf.o: ../../Source/Display/KeyboardDisplay.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling KeyboardDisplay.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/KeyPositionGraphDisplay_5606e2d0.o: ../../Source/Display/KeyPositionGraphDisplay.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling KeyPositionGraphDisplay.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/RawSensorDisplay_f15a0e36.o: ../../Source/Display/RawSensorDisplay.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling RawSensorDisplay.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/IIRFilter_c9874248.o: ../../Source/Utility/IIRFilter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling IIRFilter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Scheduler_5d9eed19.o: ../../Source/Utility/Scheduler.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Scheduler.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TimerNode_477a3545.o: ../../Source/Utility/TimerNode.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TimerNode.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TimestampSynchronizer_df7831b6.o: ../../Source/Utility/TimestampSynchronizer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TimestampSynchronizer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Trigger_66a771d6.o: ../../Source/Utility/Trigger.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Trigger.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyOscEmulator_9ad15559.o: ../../Source/TouchKeys/TouchkeyOscEmulator.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyOscEmulator.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MidiKeyboardSegment_e1be9d70.o: ../../Source/TouchKeys/MidiKeyboardSegment.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MidiKeyboardSegment.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/KeyIdleDetector_2efa023e.o: ../../Source/TouchKeys/KeyIdleDetector.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling KeyIdleDetector.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/KeyPositionTracker_4c4c0dd5.o: ../../Source/TouchKeys/KeyPositionTracker.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling KeyPositionTracker.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LogPlayback_1debad04.o: ../../Source/TouchKeys/LogPlayback.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LogPlayback.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MidiInputController_1864322a.o: ../../Source/TouchKeys/MidiInputController.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MidiInputController.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MidiOutputController_a68d4623.o: ../../Source/TouchKeys/MidiOutputController.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MidiOutputController.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Osc_433b9284.o: ../../Source/TouchKeys/Osc.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Osc.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/OscMidiConverter_75608f25.o: ../../Source/TouchKeys/OscMidiConverter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling OscMidiConverter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PianoKey_1afca9bb.o: ../../Source/TouchKeys/PianoKey.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PianoKey.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PianoKeyboard_f097ab55.o: ../../Source/TouchKeys/PianoKeyboard.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PianoKeyboard.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PianoKeyCalibrator_6932659c.o: ../../Source/TouchKeys/PianoKeyCalibrator.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PianoKeyCalibrator.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PianoPedal_34544d96.o: ../../Source/TouchKeys/PianoPedal.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PianoPedal.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TouchkeyDevice_be3b7a9b.o: ../../Source/TouchKeys/TouchkeyDevice.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TouchkeyDevice.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainApplicationController_90b344b4.o: ../../Source/MainApplicationController.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainApplicationController.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_5460bccb.o: ../../../juce/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_44d00ac9.o: ../../../juce/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_73515469.o: ../../../juce/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_5f5a3bad.o: ../../../juce/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_7e517fa9.o: ../../../juce/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_88dd09a1.o: ../../../juce/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_29b23085.o: ../../../juce/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_a9efcd81.o: ../../../juce/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_a9396b49.o: ../../../juce/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_opengl_492531cd.o: ../../../juce/modules/juce_opengl/juce_opengl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_opengl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
