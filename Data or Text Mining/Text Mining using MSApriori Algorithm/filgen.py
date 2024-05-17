import random

max_num = 25
min_sup = 0.0005
max_sup = 0.0100


def generate_data_file(filename, num_transactions, max_items_per_transaction):
  with open(filename, 'w') as file:
    for _ in range(num_transactions):
      transaction = ', '.join(
          str(random.randint(1, max_num))
          for _ in range(random.randint(1, max_items_per_transaction)))
      file.write(transaction + '\n')


def generate_param_file(filename, num_items):
  with open(filename, 'w') as file:
    for i in range(1, random.randint(1, num_items)):
      file.write(f"MIS({i}) = {random.uniform(min_sup, max_sup):.3f}\n")
    file.write(f"MIS(rest) = {random.uniform(min_sup, max_sup):.3f}\n")
    file.write(f"SDC = {random.uniform(0, 0.0400):.3f}\n")


data_filename = 'big_data.txt'
param_filename = 'big_params.txt'

num_transactions = 10000  # Increase this value to generate more transactions
max_items_per_transaction = 15  # Increase this value to generate more items per transaction
num_items = max_num  # Increase this value to generate more unique items

generate_data_file(data_filename, num_transactions, max_items_per_transaction)
generate_param_file(param_filename, num_items)

print(
    f"Large data file '{data_filename}' and parameter file '{param_filename}' generated successfully."
)
