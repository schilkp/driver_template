from os import listdir, makedirs
from os.path import isfile, join
from string import Template

# ###### TODO: ADAPT SETTINGS ######

# Select template:
template = "funcpack"
# template = "macromap"
# template = "macromap_zephyr"

# Adapt Settings:
settings = {
    'driver_name': "LSM6DSM",
    'driver_name_code': "lsm6dsm",
    'driver_name_macro': "lsm6dsm",
    'driver_name_file': "lsm6dsm",

    'author_name': "Philipp Schilk",
    'author_affiliation': "",

    # Zephyr specific:
    'driver_name_zephyr': "REGULATOR_MAX77654",
    'zephyr_dts': "maxim,regulator_max77654",
    'zephyr_dts_compat': "maxim_regulator_max77654",

    # Reginald specific:
    'reginald_commit_lock': "69cdee4",
}

# #################################


def convert_file_name(n, settings):
    for key, val in settings.items():
        if ('__' + key + '__') in n:
            n = n.replace('__' + key + '__', val)
    return n


def convert_file(input_path, output_path, settings):
    print(f"{input_path} -> {output_path}")

    with open(input_path, 'r') as input_file:
        input_lines = input_file.readlines()

    output_lines = []
    for input_line in input_lines:
        try:
            output_lines.append(Template(input_line).substitute(settings))
        except ValueError as k:
            print(f"ERROR IN FILE {input_path}")
            print(f"LINE {input_line}")
            print(k)
            exit(-1)

    with open(output_path, 'w') as output_file:
        output_file.writelines(output_lines)


def convert_directory(input_path, output_path, settings):
    makedirs(output_path)

    for thing_name in listdir(input_path):
        thing_input_path = join(input_path, thing_name)
        thing_output_path = join(output_path, convert_file_name(thing_name, settings))

        if isfile(thing_input_path):
            convert_file(thing_input_path, thing_output_path, settings)
        else:
            convert_directory(thing_input_path, thing_output_path, settings)


def main():
    input_path = join('template', template, '__driver_name_file__')
    output_path = join('output', convert_file_name('__driver_name_file__', settings))
    convert_directory(input_path, output_path, settings)


if __name__ == '__main__':
    main()
