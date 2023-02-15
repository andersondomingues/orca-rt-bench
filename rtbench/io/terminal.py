from datetime import datetime

TERMINAL_ENABLE_DEBUG = True
TERMINAL_ENDLINE = "\n\r"


COLORS = {
    "BLUE": "\033[94m",
    "CYAN": "\033[96m",
    "GREEN": "\033[92m",
    "YELLOW": "\033[93m",
    "RED": "\033[91m",
}


class colors:
    BOLD = "\033[1m"
    UNDERLINE = "\033[4m"
    HEADER = "\033[95m"
    END = "\033[0m"
    WARN = COLORS["YELLOW"]
    ERROR = COLORS["RED"]
    DEBUG = COLORS["CYAN"]
    INFO = COLORS["GREEN"]


def info(*msg, end=TERMINAL_ENDLINE):
    raw_print("warn", msg, colors.INFO, end)


def error(*msg, end=TERMINAL_ENDLINE):
    raw_print("warn", msg, colors.ERROR, end)


def header(*msg, end=TERMINAL_ENDLINE):
    raw_print("warn", msg, colors.HEADER, end)


def debug(*msg, end=TERMINAL_ENDLINE):
    if TERMINAL_ENABLE_DEBUG:
        raw_print("warn", msg, colors.DEBUG, end)


def warn(*msg, end=TERMINAL_ENDLINE):
    raw_print("warn", msg, colors.WARN, end)


def raw_print(label, msg, cbegin, end=TERMINAL_ENDLINE):
    now = datetime.now()
    strnow = now.strftime("%H:%M:%S")
    args = " ".join([str(i) for i in msg])
    print(f"{cbegin} [{label} {strnow}] {args}{colors.END}", end=end)
