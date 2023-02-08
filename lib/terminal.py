from datetime import datetime

TERMINAL_ENABLE_DEBUG = False
TERMINAL_ENDLINE = "\n\r"


def info(msg, end=TERMINAL_ENDLINE):
    now = datetime.now()
    # strnow = now.strftime("%m/%d/%Y, %H:%M:%S")
    strnow = now.strftime("%H:%M:%S")
    print(colors.OK + "[info " + strnow + "] " + str(msg) + colors.END, end=end)


def error(msg, end=TERMINAL_ENDLINE):
    now = datetime.now()
    # strnow = now.strftime("%m/%d/%Y, %H:%M:%S")
    strnow = now.strftime("%H:%M:%S")
    print(colors.ERROR + "[error " + strnow + "] " + str(msg) + colors.END, end=end)


def header(msg, end=TERMINAL_ENDLINE):
    print(colors.HEADER + msg + colors.END, end=end)


def debug(msg, end=TERMINAL_ENDLINE):
    if TERMINAL_ENABLE_DEBUG:
        now = datetime.now()
        # strnow = now.strftime("%m/%d/%Y, %H:%M:%S")
        strnow = now.strftime("%H:%M:%S")
        print(colors.DEBUG + "[debug " + strnow + "] " + str(msg) + colors.END, end=end)


def warn(msg, end=TERMINAL_ENDLINE):
    now = datetime.now()
    # strnow = now.strftime("%m/%d/%Y, %H:%M:%S")
    strnow = now.strftime("%H:%M:%S")
    print(colors.WARN + "[warn " + strnow + "] " + str(msg) + colors.END, end=end)


class colors:
    HEADER = "\033[95m"

    BLUE = "\033[94m"
    CYAN = "\033[96m"
    GREEN = "\033[92m"
    YELLOW = "\033[93m"
    RED = "\033[91m"

    BOLD = "\033[1m"
    UNDERLINE = "\033[4m"

    END = "\033[0m"

    WARN = YELLOW
    ERROR = RED
    DEBUG = CYAN
    OK = GREEN
