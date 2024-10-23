import tkinter as tk
from tkinter import ttk, scrolledtext
import threading
import serial


class SerialApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Serial Port Communication")

        self.bytes_sent = 0
        self.current_data = ""
        self.port1 = None
        self.port2 = None
        self.serial1 = None
        self.serial2 = None
        self.running = True

        self.create_widgets()
        self.get_available_ports()

    def create_widgets(self):
        # Окно ввода
        self.input_frame = ttk.Frame(self.root)
        self.input_frame.pack(fill=tk.BOTH, expand=True)
        self.input_label = ttk.Label(self.input_frame, text="Input window")
        self.input_label.pack(side=tk.TOP)
        self.input_text = scrolledtext.ScrolledText(
            self.input_frame, height=6, wrap=tk.CHAR
        )
        self.input_text.pack(fill=tk.BOTH, expand=True)
        self.input_text.bind("<Key>", self.send_data)
        self.input_text.config(state="disabled")

        # Окно вывода
        self.output_frame = ttk.Frame(self.root)
        self.output_frame.pack(fill=tk.BOTH, expand=True)
        self.output_label = ttk.Label(self.output_frame, text="Output window")
        self.output_label.pack(side=tk.TOP)
        self.output_text = scrolledtext.ScrolledText(
            self.output_frame, height=6, wrap=tk.CHAR, state="disabled"
        )
        self.output_text.pack(fill=tk.BOTH, expand=True)

        # Окно управления
        self.control_frame = ttk.Frame(self.root)
        self.control_frame.pack(fill=tk.X)
        self.port_frame = ttk.Frame(self.control_frame)
        self.port_frame.pack(side=tk.TOP, pady=5)

        self.port1_label = ttk.Label(self.control_frame, text="Port 1 (sender):")
        self.port1_label.pack(side=tk.TOP, anchor="center")
        self.port1_combobox = ttk.Combobox(
            self.control_frame, values=self.get_available_ports(), state="readonly"
        )
        self.port1_combobox.pack(side=tk.TOP, anchor="center")
        self.port1_combobox.bind("<<ComboboxSelected>>", self.check_ports)

        self.port2_label = ttk.Label(self.control_frame, text="Port 2 (receiver):")
        self.port2_label.pack(side=tk.TOP, anchor="center")
        self.port2_combobox = ttk.Combobox(
            self.control_frame, values=self.get_available_ports(), state="readonly"
        )
        self.port2_combobox.pack(side=tk.TOP, anchor="center")
        self.port2_combobox.bind("<<ComboboxSelected>>", self.check_ports)

        # Окно состояния
        self.status_frame = ttk.Frame(self.root)
        self.status_frame.pack(fill=tk.X, side=tk.TOP, pady=10)
        self.status_label = ttk.Label(self.status_frame, text="Status window")
        self.status_label.pack(side=tk.TOP)
        self.status_text = tk.Text(
            self.status_frame, height=3, wrap=tk.WORD, state="disabled", bg="#f0f0f0"
        )
        self.status_text.pack(side=tk.LEFT, fill=tk.X, expand=True)

        # Отладочное окно
        self.debug_frame = ttk.Frame(self.root)
        self.debug_frame.pack(fill=tk.BOTH, expand=True)
        self.debug_label = ttk.Label(self.debug_frame, text="Debug window")
        self.debug_label.pack(side=tk.TOP)
        self.debug_text = scrolledtext.ScrolledText(
            self.debug_frame, height=6, state="disabled"
        )
        self.debug_text.pack(fill=tk.BOTH, expand=True)

    def get_available_ports(self):
        ports = []
        for i in range(256):
            try:
                s = serial.Serial(f"COM{i}")
                ports.append(f"COM{i}")
                s.close()
            except (OSError, serial.SerialException):
                pass
        return ports

    def update_ports_for_first(self):
        ports = self.get_available_ports()
        if self.port2:
            ports.remove(self.port2)
            prev_port_index = int(self.port2.replace("COM", "")) - 1
            if prev_port_index >= 1:
                prev_port = f"COM{prev_port_index}"
                if prev_port in ports:
                    ports.remove(prev_port)
        self.port1_combobox["values"] = ports

    def update_ports_for_second(self):
        ports = self.get_available_ports()
        if self.port1:
            ports.remove(self.port1)
            next_port_index = int(self.port1.replace("COM", "")) + 1
            next_port = f"COM{next_port_index}"
            if next_port in ports:
                ports.remove(next_port)
        self.port2_combobox["values"] = ports

    def check_ports(self, event):
        selected_port1 = self.port1_combobox.get()
        selected_port2 = self.port2_combobox.get()

        if event.widget == self.port1_combobox:
            if self.serial1 and self.serial1.is_open:
                self.serial1.close()
            self.port1 = selected_port1
            self.update_ports_for_second()

        elif event.widget == self.port2_combobox:
            if self.serial2 and self.serial2.is_open:
                self.serial2.close()
            self.port2 = selected_port2
            self.update_ports_for_first()

        if self.port1 and self.port2:
            self.connect_ports()

    def connect_ports(self):
        # Закрытие предыдущих подключений если они есть
        if self.serial1:
            self.serial1.close()
        if self.serial2:
            self.serial2.close()

        # Очистка окон ввода и вывода
        self.input_text.config(state="normal")  # Включаем редактирование
        self.input_text.delete(1.0, tk.END)  # Очищаем
        self.input_text.config(state="disabled")  # Выключаем редактирование
        self.output_text.config(state="normal")
        self.output_text.delete(1.0, tk.END)
        self.output_text.config(state="disabled")

        # Открытие соединения с выбранными портами
        self.serial1 = serial.Serial(self.port1, 9600, timeout=1)
        self.serial2 = serial.Serial(self.port2, 9600, timeout=1)

        # Обновление статуса подключения и сброс счетчиков
        self.status_text.config(state="normal")
        self.status_text.delete(1.0, tk.END)  # Очистка текста
        self.status_text.insert(
            tk.END,
            f"Connected to {self.port1} and {self.port2}\n"
            f"baudrate: {self.serial1.baudrate}, "
            f"bytesize: {self.serial1.bytesize}, "
            f"parity: {self.serial1.parity}, "
            f"stopbits: {self.serial1.stopbits}, "
            f"timeout: {self.serial1.timeout}, "
            f"xonxoff: {self.serial1.xonxoff}, "
            f"rtscts: {self.serial1.rtscts}, "
            f"dsrdtr: {self.serial1.dsrdtr}, "
            f"write_timeout: {self.serial1.write_timeout}, "
            f"inter_byte_timeout: {self.serial1.inter_byte_timeout}",
        )
        self.status_text.config(state="disabled")
        self.bytes_sent = 0
        # Демон-поток автоматически завершится, когда завершится основной поток
        threading.Thread(target=self.read_serial, daemon=True).start()

    def send_data(self, event):
        if event.char in ("0", "1") or event.keysym == "Return":
            if event.keysym == "Return":
                event.char = "\n"
            self.bytes_sent += len(event.char.encode("utf-8"))

            if self.serial1.is_open and self.serial2.is_open:
                self.current_data += event.char
                self.update_debug(f"Symbol: {repr(event.char)}")

                if len(self.current_data) == 2:
                    packet = self.create_frame(self.current_data)
                    self.serial1.write(packet.encode())
                    self.update_status(packet)
                    self.current_data = ""

            self.input_text.config(state="normal")
            self.input_text.insert(tk.END, event.char)
            self.input_text.see(tk.END)
            self.input_text.config(state="disabled")

        else:
            return

    def read_serial(self):
        while self.running:
            if self.serial2.in_waiting > 0:
                data = self.serial2.read(self.serial2.in_waiting)
                data_decoded = self.bit_unstuffing(
                    data.decode("utf-8", errors="ignore")
                )
                data_content = data_decoded[16:18]
                self.output_text.config(state="normal")
                self.output_text.insert(tk.END, data_content)
                self.output_text.see(tk.END)
                self.output_text.config(state="disabled")
                self.update_debug(f"Received: {repr(data_content)}")

    def create_frame(self, data):
        flag = "10000010"
        destination_address = "0000"
        source_address = format(int(self.port1.replace("COM", "")), "04b")
        fcs = "0"
        bits = destination_address + source_address + data + fcs
        frame = flag + self.bit_stuffing(bits)
        return frame

    def bit_stuffing(self, bits):
        stuffed_frame = ""
        flag = "100000"
        i = 0
        while i < len(bits):
            if bits[i : i + 6] == flag:
                stuffed_frame += bits[i : i + 6] + "0"
                i += 6
            else:
                stuffed_frame += bits[i]
                i += 1
        return stuffed_frame

    def bit_unstuffing(self, bits):
        unstuffed_frame = ""
        flag = "1000000"
        i = 0
        while i < len(bits):
            if bits[i : i + 7] == flag:
                unstuffed_frame += bits[i : i + 6]
                i += 7
            else:
                unstuffed_frame += bits[i]
                i += 1
        return unstuffed_frame

    def update_status(self, frame):
        flag = "1000000"
        text = f"Sent: {self.bytes_sent} bytes\n{repr(frame)}\n"
        self.status_text.config(state="normal")
        self.status_text.delete(1.0, tk.END)
        self.status_text.tag_remove("highlight", "1.0", tk.END)
        self.status_text.insert(tk.END, text)
        self.status_text.tag_config("highlight", background="yellow")
        start_index = text.find("10000010")
        i = start_index + 8
        while i < len(text):
            if text[i : i + 7] == flag:
                index = i + 6
                self.status_text.tag_add(
                    "highlight", f"1.0 + {index} chars", f"1.0 + {index + 1} chars"
                )
                i += 1
            else:
                i += 1
        self.status_text.config(state="disabled")

    def update_debug(self, message):
        self.debug_text.config(state="normal")
        self.debug_text.insert(tk.END, message + "\n")
        self.debug_text.see(tk.END)
        self.debug_text.config(state="disabled")

    def on_closing(self):
        self.running = False
        if self.serial1:
            self.serial1.close()
        if self.serial2:
            self.serial2.close()
        self.root.destroy()


if __name__ == "__main__":
    root = tk.Tk()
    app = SerialApp(root)
    root.protocol("WM_DELETE_WINDOW", app.on_closing)
    root.minsize(400, 500)
    root.mainloop()
