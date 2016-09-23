from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.button import Button

from kivy.lang import Builder
from kivy.core.window import Window
from kivy.uix.vkeyboard import VKeyboard
from kivy.properties import ObjectProperty
from kivy.uix.button import Button

from kivy.config import Config
from kivy.uix.screenmanager import Screen, ScreenManager
from kivy import require






class KioskMainUi(Screen):
    """
    Present the option to change keyboard mode and warn of system-wide
    consequences.
    """
    center_label = ObjectProperty()
    mode_spinner = ObjectProperty()

    keyboard_mode = ""

    def on_pre_enter(self, *args):
        """ Detect the current keyboard mode and set the text of the main
        label accordingly. """

        self.keyboard_mode = Config.get("kivy", "keyboard_mode")
        self.mode_spinner.text = "'{0}'".format(self.keyboard_mode)

        p1 = "Current keyboard mode: '{0}'\n\n".format(self.keyboard_mode)
        if self.keyboard_mode in ['dock', 'system', 'systemanddock']:
            p2 = "You have the right setting to use this demo.\n\n"
        else:
            p2 = "You need the keyboard mode to 'dock', 'system' or '"\
                 "'systemanddock'(below)\n in order to "\
                 "use custom onscreen keyboards.\n\n"

        p3 = "[b][color=#ff0000]Warning:[/color][/b] This is a system-wide " \
            "setting and will affect all Kivy apps. If you change the\n" \
            " keyboard mode, please use this app" \
            " to reset this value to it's original one."

        self.center_label.text = "".join([p1, p2, p3])

    def set_mode(self, mode):
        """ Sets the keyboard mode to the one specified """
        Config.set("kivy", "keyboard_mode", mode.replace("'", ""))
        Config.write()
        self.center_label.text = "Please restart the application for this\n" \
            "setting to take effect."

    def next(self):
        """ Continue to the main screen """
        self.manager.current = "keyboard"



class KioskApp(App):

    def build(self):
        self.sm = ScreenManager()
        self.sm.add_widget(KioskMainUi(name="mode"))
        #self.sm.add_widget(KeyboardScreen(name="keyboard"))
        self.sm.current = "mode"
        return self.sm



if __name__ == '__main__':
    from kivy.core.window import Window
    #Window.fullscreen = True
    Window.rotation=90
    KioskApp().run()
