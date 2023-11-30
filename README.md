# BitTorrent-Client

This project implements a basic peer-to-peer (P2P) file-sharing system, similar to BitTorrent, using socket programming in C++. It features a client-server architecture where clients can upload, download, and share files within groups, while the server (tracker) manages connections and data integrity.

## Features

- Password-based user authentication.
- Group-based file sharing.
- File upload and download with parallel data transfer.
- Data integrity verification using SHA1 hashes.
- Redundant tracker system for improved reliability.

## Getting Started

### Prerequisites

- C++ compiler (g++ recommended)
- Make (for building the project)

### Installation

1. Clone the repository: git clone https://github.com/rhuthik/BitTorrent-Client.git
2. Navigate to the project directory and build the project: cd BitTorrent-Client make


### Running the Application

- Start the tracker:
./tracker <tracker_info.txt> <tracker_number>
- Run the client application:
./client IP:PORT <tracker_info.txt>

## Project Structure

- `src/` - Contains the source files for the client and tracker.
- `include/` - Header files for the client and tracker.
- `utils/` - Utility functions and classes like logging.
- `config/` - Configuration files like `tracker_info.txt`.


