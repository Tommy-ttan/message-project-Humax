# **Client**
## 1. Functional
- able to connect to the server
- no login, no database, no history
- able to select role when app starts
- 3 roles:
  - listener:
    - only receive messages from the time of connecting to the server successfully. 
    - Not able to poll server for incoming data
  - talker: only send messages to server
  - listener and talker: do both things
## 2. Non-functional
- has log out option
- *talker client*: able to erase wrong character when inputing message
- *both client*: received message section and input message section are seperated in UI
- has instruction UI for user

# **Server**
## 1. Functional
- able to receive from and send message to clients
- no limited number of clients connected to
- be aware of new client
## 2. Non-functional
- no UI

