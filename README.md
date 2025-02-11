# BIDFIC Auction System

## Overview
BIDFIC is a program that manages an auction system where users can list products, place bids, and track auction outcomes. The program implements two primary abstract data types (ADTs):

- **Product List**: A dynamically allocated ordered list to store products.
- **Bid Stack**: A static stack to manage bids for each product.

The system allows users to add products, place bids, withdraw bids, assign auction winners, and remove products with no bids.

## Data Structures
### Product List (Ordered List)
This ADT manages an ordered list of products, sorted alphabetically by their unique product ID. Each product contains:

- **Seller ID**: Identifier of the user selling the product.
- **Product ID**: Unique identifier of the product.
- **Category**: Product category (e.g., book, painting).
- **Price**: Initial price of the product.
- **Bid Counter**: Number of bids received.
- **Bid Stack**: Stack storing the bids for the product.

### Bid Stack (Stack)
This ADT manages bids placed on a product using a static stack with a maximum of 25 elements. Each bid consists of:

- **Bidder ID**: Identifier of the user placing the bid.
- **Bid Amount**: The amount the bidder is offering.

## Supported Operations
The program reads commands from an input file and processes auction-related operations. Each command consists of a single character followed by relevant data:

- `N productId userId productCategory productPrice` → Adds a new product.
- `D productId` → Deletes a product if it has no bids.
- `B productId userId productPrice` → Places a bid on a product.
- `A productId` → Awards the product to the highest bidder and removes it from the list.
- `W productId userId` → Withdraws the current highest bid for a product.
- `R` → Removes products that have no bids.
- `S` → Displays the current product list, bids, and auction statistics.

## Execution
The program processes commands from an input file in a loop, displaying output for each command. No manual input is required, as the program reads from predefined scripts.

## Output Format
Each operation produces a structured output. For instance:

- Successfully adding a product:
  ```
  * New: product P001 seller U001 category book price 15.00
  ```
- Error due to duplicate product ID:
  ```
  + Error: New not possible
  ```
- Placing a bid:
  ```
  * Bid: product P001 bidder U002 category book price 20.00 bids 1
  ```
- Awarding a product:
  ```
  * Award: product P001 bidder U002 category book price 20.00
  ```
- Displaying auction statistics:
  ```
  Product P001 seller U001 category book price 15.00 bids 2 top bidder U002
  Category  Products  Price  Average
  Book        1       15.00   15.00
  ```

## Error Handling
The program handles cases such as:
- Attempting to delete a product with active bids.
- Placing a bid that does not exceed the current highest bid.
- Awarding a product without any bids.
- Trying to withdraw a bid that does not exist.

## Conclusion
This project demonstrates the use of abstract data types to implement an auction system, focusing on ordered lists and stacks. The system efficiently manages auction operations while ensuring data integrity through structured error handling.
