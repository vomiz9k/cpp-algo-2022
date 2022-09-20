from unittest import expectedFailure
import pytest
import os
from random import choices, randint
from string import ascii_uppercase


input_filename = "input"
output_filename = "output"

def trade_type(order_type):
    return "long" if order_type == "buy" else "short"

def another_order_type(order_type):
    return "sell" if order_type == "buy" else "buy"

def launch_exchange(input_text, expected_text, mode):
    with open(input_filename, "w") as f:
        f.write(input_text)
    os.system("./exchange.out {} {} {}".format(input_filename, output_filename, mode))
    with open(output_filename) as f:
        assert f.read() == expected_text

    os.remove(input_filename)
    os.remove(output_filename)

def generate_random_string(size):
    return ''.join(choices(ascii_uppercase, k=size))

@pytest.mark.parametrize("order_type", ["buy", "sell"])
@pytest.mark.parametrize("size", [1, 10, 100, 1000])
@pytest.mark.parametrize("mode", ["first", "last"])
def test_single_company(mode, size, order_type):
    input_text = ''.join(["{} {} Apple 10 150\n".format(str(i), order_type) for i in range(1, size + 1)])
    expected_text = ''.join(["Apple 10 150 - - {} {}\n".format(trade_type(order_type), str(i)) for i in range(1, size + 1)])
    launch_exchange(input_text, expected_text, mode)

@pytest.mark.parametrize("order_type", ["buy", "sell"])
@pytest.mark.parametrize("size", [1, 10, 100, 1000])
@pytest.mark.parametrize("mode", ["first", "last"])
def test_multiple_companies(mode, size, order_type):
    input_text = ''.join(["{} {} Apple 10 150\n".format(str(i), order_type) for i in range(1, size + 1)]) + \
                 ''.join(["{} {} Google 10 150\n".format(str(i), order_type) for i in range(size + 1, 2 * size + 1)]) + \
                 ''.join(["{} {} Apple 10 150\n".format(str(i), order_type) for i in range(2 * size + 1, 3 * size + 1)])

    expected_text = ''.join(["Apple 10 150 - - {} {}\n".format(trade_type(order_type), str(i)) for i in range(1, size + 1)]) + \
                    ''.join(["Apple 10 150 - - {} {}\n".format(trade_type(order_type), str(i)) for i in range(2 * size + 1, 3 * size + 1)]) + \
                    ''.join(["Google 10 150 - - {} {}\n".format(trade_type(order_type), str(i)) for i in range(size + 1, 2 * size + 1)])
    launch_exchange(input_text, expected_text, mode)

@pytest.mark.parametrize("size", [1, 10, 100, 1000])
@pytest.mark.parametrize("order_type", ["buy", "sell"])
@pytest.mark.parametrize("mode", ["first", "last"])
def test_simple_trades(mode, order_type, size):
    input_text = ''.join(["{} {} Apple 10 150\n".format(str(i), order_type) + \
                 "{} {} Apple 10 160\n".format(str(i + 1), another_order_type(order_type)) for i in range(1, 2 * size + 1, 2)])
    expected_text = ''.join(["Apple 10 150 160 {}100 {} {} {}\n".format("-" if order_type == "sell" else "", trade_type(order_type), str(i), str(i + 1)) for i in range(1, 2 * size + 1, 2)])
    launch_exchange(input_text, expected_text, mode)

@pytest.mark.parametrize("mode", ["first", "last"])
def test_modes(mode):
    input_text = "1 buy Apple 5 150\n" + \
                 "2 buy Apple 5 160\n" + \
                 "3 sell Apple 10 310\n"
    output_lines = ["Apple 5 160 310 750 long 2 3\n", "Apple 5 150 310 800 long 1 3\n"]
    expected_text = ''.join(output_lines if mode == "last" else output_lines[::-1])
    launch_exchange(input_text, expected_text, mode)

@pytest.mark.parametrize("mode", ["first", "last"])
def test_example(mode):
    input_text = "1 buy Apple 10 150\n" + \
                 "2 buy Apple 5 140\n" + \
                 "3 sell Apple 5 145\n" + \
                 "4 sell Apple 15 155\n" + \
                 "5 buy Apple 15 135\n"
    expected_text = "Apple 5 150 145 -25 long 1 3\n" + \
                    "Apple 5 150 155 25 long 1 4\n" + \
                    "Apple 5 140 155 75 long 2 4\n" + \
                    "Apple 5 155 135 100 short 4 5\n" + \
                    "Apple 10 135 - - long 5\n" \
                        if mode == "first" else \
                    "Apple 5 140 145 25 long 2 3\n" + \
                    "Apple 10 150 155 50 long 1 4\n" + \
                    "Apple 5 155 135 100 short 4 5\n" + \
                    "Apple 10 135 - - long 5\n"
    launch_exchange(input_text, expected_text, mode)


@pytest.mark.parametrize("size", [1, 10, 100, 1000, 10000, 100000, 1000000])
@pytest.mark.parametrize("mode", ["first", "last"])
def test_output_is_sorted(size, mode):
    companies_cnt = size // 10 + 1
    companies = [generate_random_string(10) for i in range(companies_cnt)]
    input_text = ["{} {} {} {} {}\n".format(str(i + 1),
                                            "buy" if randint(0, 1) else "sell",
                                            companies[randint(0, companies_cnt - 1)],
                                            randint(5, 10),
                                            randint(100, 200)) for i in range(size)]
    with open(input_filename, "w") as f:
        f.write(''.join(input_text))

    os.system("./exchange.out {} {} {}".format(input_filename, output_filename, mode))
    with open(output_filename) as f:
        lines = f.read().split('\n')[:-1]
        names = list(map(lambda x: x.split(' ')[0], lines))
        assert all(names[i] <= names[i+1] for i in range(len(names) - 1))
        names_and_ids = list(map(lambda x: (x.split(' ')[0], (x.split(' ')[7] if len(x.split(' ')) >= 8 else "-")), lines))
        d = dict()
        for name, id in names_and_ids:
            if name not in d:
                d[name] = []
            d[name].append(id)

        for key in d:
            arr = d[key]
            last_empty = len(arr) - 1
            while(last_empty >= 0 and arr[last_empty] == "-"):
                last_empty -= 1
            if (last_empty < 0):
                continue
            last_empty += 1
            arr = arr[:last_empty]
            arr = list(map(int, arr))
            assert all(arr[i] <= arr[i+1] for i in range(len(arr) - 1))
    os.remove(input_filename)
    os.remove(output_filename)
