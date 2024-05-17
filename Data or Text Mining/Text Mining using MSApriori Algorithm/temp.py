from itertools import combinations


# Function to calculate support count for pairs of integers
def calculate_support_count(transactions):
    support_count = {}

    # Iterate through each transaction
    for transaction in transactions:
        if not transaction:  # Skip empty transactions
            continue

        # Remove duplicates within the transaction
        transaction = list(set(transaction))

        # Generate pairs of integers from the transaction
        pairs = combinations(transaction, 4)  # Changed to combinations of size 2

        # Increment support count for each pair
        for pair in pairs:
            pair_set = frozenset(pair)  # Use frozenset to make pairs unordered
            if pair_set in support_count:
                support_count[pair_set] += 1
            else:
                support_count[pair_set] = 1

    return support_count


# Read data from file
def read_transactions_from_file(filename):
    transactions = []
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip()
            if not line:  # Skip empty lines
                continue
            # Remove trailing comma if present
            if line.endswith(","):
                line = line[:-1]
            transaction = list(map(int, line.split(',')))
            transactions.append(transaction)
    return transactions


# Input file name
filename = "data-2.txt"

# Read transactions from file
data = read_transactions_from_file(filename)

# Calculate support count for all pairs
result = calculate_support_count(data)

for e in result:
    print(e, ":", result[e])

# Specify the pair you're interested in
specific_pair = frozenset({2, 4, 7, 9})  # Change the numbers as needed

# Output support count for the specific pair
if specific_pair in result:
    print(f"Support count for pair {specific_pair}: {result[specific_pair]}")
else:
    print(f"Support count for pair {specific_pair}: 0")
