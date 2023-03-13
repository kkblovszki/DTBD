import numpy as np
import dearpygui.dearpygui as dpg
import time
import yaml

dpg.create_context()

class DataHandler:
    
    def __init__(self):
        # Resize
        self.main_window_size = [-1, -1]
        self.scale = [0.3, 0.7]
        self.plot_size = [-1, -1]
        self.plot_window_min_width = -1
        self.data_pool_min_width = -1

        # UI design
        self.delta_width_vp = 17                # viewport width - non-primary window width
        self.delta_height_vp = 40               # viewport height - non-primary window height
        self.delta_height_child = 15            # non-primary window height - child height
        self.vertical_separator_width = 15
        pass
    
    def update(self):
        pass
    
    def add_plot():
        pass
    
    def load_data():
        pass

    def list_simulators():
        pass
    
    def list_scenarios(simulator_type):
        pass
    
    def list_parameters(scenario):
        pass