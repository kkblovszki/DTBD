"""try:
    from .DataHandler import DataHandler
except:
    raise ImportError('Class DataHandler not found.')"""

import dearpygui.dearpygui as dpg

dpg.create_context()

#window settings
with dpg.font_registry():
    # first argument ids the path to the .ttf or .otf file
    default_font = dpg.add_font("CascadiaMono.ttf", 20)

with dpg.window(label="Testbed", width=520, height=440):
    with dpg.menu_bar():
        with dpg.menu(label="Import data"):
            dpg.add_menu_item(label="Import CSV")
            dpg.add_menu_item(label="Import JSON")
        dpg.add_button(label="Build and Launch Simulator")
    dpg.bind_font(default_font)

with dpg.window(label="Plots", pos=[530, 0], width=1060, height=890):
    dpg.add_simple_plot(label="Simpleplot1", default_value=(0.3, 0.9, 0.5, 0.3), height=440)
    dpg.add_simple_plot(label="Simpleplot2", default_value=(0.3, 0.9, 2.5, 8.9), overlay="Overlaying", height=440,
                        histogram=True)

with dpg.window(label="Data", width=520, height=440, pos=[0, 450]):
    with dpg.table(header_row=False):

        # use add_table_column to add columns to the table,
        # table columns use child slot 0
        dpg.add_table_column()
        dpg.add_table_column()
        dpg.add_table_column()

        # add_table_next_column will jump to the next row
        # once it reaches the end of the columns
        # table next column use slot 1
        for i in range(0, 4):
            with dpg.table_row():
                for j in range(0, 3):
                    dpg.add_text(f"Row{i} Column{j}")

#Run the whole thing
dpg.create_viewport(title="Testbench", width=1600, height=900)
dpg.setup_dearpygui()
dpg.show_viewport()
dpg.start_dearpygui()
dpg.destroy_context()