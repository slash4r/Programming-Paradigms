import subprocess


def print_green(text):
    print(f"\033[92m{text}\033[00m", end="")


def print_yellow(text):
    print(f"\033[93m{text}\033[00m", end="")


def run_echo(input_data):
    process = subprocess.Popen(
        ['Program.exe'],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    stdout, stderr = process.communicate(input_data)
    return stdout.strip(), stderr.strip()


def test_echo():
    tests = [
        {
            "input": "5 + 3 * 2\n",
            "expected_output": "Result: 11"
        },
        {
            "input": "max(5, 2)\n",
            "expected_output": "Result: 5"
        },
        {
            "input": "min(3, 4)\n",
            "expected_output": "Result: 3"
        },
        {
            "input": "abs(-3)\n",
            "expected_output": "Result: 3"
        },
        {
            "input": "max(min(3 * 2, 2), pow(2, 3))\n",
            "expected_output": "Result: 8"
        },
        {
            "input": "max(min(3 * 2, 2), pow(2, 3)) + 61\n",
            "expected_output": "Result: 69"
        },
        {
            "input": "var a = max(min(3 * 2, 2), 2)\n"
                     "var b = pow(2, 3)\n"
                     "a + b\n",
            "expected_output": "Result: 10"
        }
    ]

    for test in tests:
        input_data = test["input"]
        expected_output = test["expected_output"]

        output, error = run_echo(input_data)

        if error:
            print(f"Test failed for input:\n{input_data}")
            print(f"Error:\n{error}")
        elif output.strip() != expected_output:
            print(f"Test failed for input:\n{input_data}")
            print(f"Expected:\n{expected_output}")
            print(f"Got:\n{output}")
        else:
            print_green(f"Test passed for input:\n")
            print(input_data)
            print_yellow(f"Output: ")
            print(expected_output, end="\n\n")


if __name__ == "__main__":
    test_echo()
