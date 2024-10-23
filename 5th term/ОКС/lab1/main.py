import tkinter as tk
from tkinter import ttk, scrolledtext
import threading
import serial


class SerialApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Serial Port Communication")

        self.bytes_sent = 0
        # Переменные для хранения имен COM портов
        self.port1 = None
        self.port2 = None
        # Переменные для хранения объектов соединений, созданных с pyserial
        self.serial1 = None
        self.serial2 = None
        # Флаг управления циклом чтения данных
        self.running = True

        self.create_widgets()
        self.update_ports_for_first()
        self.update_ports_for_second()

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
        self.input_text.bind('<Key>', self.send_data)
        self.input_text.config(state="disabled")

        # Окно вывода
        self.output_frame = ttk.Frame(self.root)
        self.output_frame.pack(fill=tk.BOTH, expand=True)
        self.output_label = ttk.Label(self.output_frame, text="Output window")
        self.output_label.pack(side=tk.TOP)
        self.output_text = scrolledtext.ScrolledText(
            self.output_frame, height=6, wrap=tk.CHAR, state='disabled'
        )
        self.output_text.pack(fill=tk.BOTH, expand=True)

        # Окно управления
        self.control_frame = ttk.Frame(self.root)
        self.control_frame.pack(fill=tk.X)
        self.port_frame = ttk.Frame(self.control_frame)
        self.port_frame.pack(side=tk.TOP, pady=5)

        self.port1_label = ttk.Label(self.control_frame, text="Port 1 (sender):")
        self.port1_label.pack(side=tk.TOP, anchor="center")
        self.port1_combobox = ttk.Combobox(self.control_frame, values=self.get_available_ports(), state="readonly")
        self.port1_combobox.pack(side=tk.TOP, anchor="center")
        self.port1_combobox.bind("<<ComboboxSelected>>", self.check_ports)

        self.port2_label = ttk.Label(self.control_frame, text="Port 2 (receiver):")
        self.port2_label.pack(side=tk.TOP, anchor="center")
        self.port2_combobox = ttk.Combobox(self.control_frame, values=self.get_available_ports(), state="readonly")
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

    def check_ports(self, event):
        self.port1 = self.port1_combobox.get()
        self.port2 = self.port2_combobox.get()

        if event.widget == self.port1_combobox:
            self.update_ports_for_second()
        elif event.widget == self.port2_combobox:
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
            f"inter_byte_timeout: {self.serial1.inter_byte_timeout}"
        )
        self.status_text.config(state="disabled")
        self.bytes_sent = 0
        # Демон-поток автоматически завершится, когда завершится основной поток
        threading.Thread(target=self.read_serial, daemon=True).start()

    def send_data(self, event):
        if event.keysym == "BackSpace":
            return
        if event.char:
            self.bytes_sent += len(event.char.encode("utf-8"))
            if self.serial1.is_open and self.serial2.is_open:
                if event.keysym == "Return":
                    event.char = "\n"
                self.serial1.write(event.char.encode())
                self.update_debug(f"Sent: {repr(event.char)}")
                self.update_status()
        self.input_text.config(state="normal")
        self.input_text.insert(tk.END, event.char)
        self.input_text.see(tk.END)
        self.input_text.config(state="disabled")

    def read_serial(self):
        while self.running:
            if self.serial2.in_waiting > 0:
                data = self.serial2.read(self.serial2.in_waiting)
                self.output_text.config(state="normal")
                self.output_text.insert(tk.END, data.decode("utf-8", errors="ignore"))
                self.output_text.see(tk.END)
                self.output_text.config(state="disabled")
                self.update_debug(
                    f"Received: {repr(data.decode('utf-8', errors='ignore'))}"
                )

    def update_status(self):
        self.status_text.config(state="normal")
        self.status_text.delete(1.0, tk.END)
        self.status_text.insert(tk.END, f"\nSent: {self.bytes_sent} bytes")
        self.status_text.config(state="disabled")

    def update_debug(self, message):
        self.debug_text.config(state="normal")
        self.debug_text.insert(tk.END, message + "\n")
        self.debug_text.see(tk.END)
        self.debug_text.config(state="disabled")

    def update_ports_for_first(self):
        ports = self.get_available_ports()
        # Удаляем выбранный второй порт и предыдущий по порядку
        if self.port2 in ports:
            ports.remove(self.port2)
            prev_port_index = int(self.port2.replace("COM", "")) - 1
            # Проверяем на допустимый номер порта
            if prev_port_index >= 1:
                prev_port = f"COM{prev_port_index}"
                if prev_port in ports:
                    ports.remove(prev_port)
        self.port1_combobox["values"] = ports

    def update_ports_for_second(self):
        ports = self.get_available_ports()
        # Удаляем выбранный первый порт и следующий за ним
        if self.port1 in ports:
            ports.remove(self.port1)
            next_port_index = int(self.port1.replace("COM", "")) + 1
            next_port = f"COM{next_port_index}"
            if next_port in ports:
                ports.remove(next_port)
        # Обновляем список для второго порта
        self.port2_combobox["values"] = ports

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


