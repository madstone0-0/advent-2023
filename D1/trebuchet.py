from pathlib import Path

nums = {
    "one": 1,
    "two": 2,
    "three": 3,
    "four": 4,
    "five": 5,
    "six": 6,
    "seven": 7,
    "eight": 8,
    "nine": 9,
}


def findAlphaNumFromIndex(line: str, index: int = 0) -> int | None:
    number = None
    for num in nums.keys():
        checked = line[index : index + len(num)]
        if checked == num:
            number = nums[num]
            break
    return number


def findNumber(line: str) -> int:
    first_num = -1
    temp_num = 0
    last_num = 0

    for i in range(len(line)):
        number = findAlphaNumFromIndex(line, i)
        if number and first_num == -1:
            first_num = number
        temp_num = number if number else temp_num

        c = line[i]
        if c.isdigit():
            if first_num == -1:
                first_num = int(c)
            temp_num = int(c)
    if i == len(line) - 1:
        last_num = temp_num

    return int(f"{first_num}{last_num}")


sum = 0
inputPath = Path(__file__).parent / "input.txt"
with open(inputPath, mode="r") as input:
    for line in input.readlines():
        sum += findNumber(line)

print(sum)
