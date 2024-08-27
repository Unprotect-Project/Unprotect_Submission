import requests, json, argparse

apiKey = ""


def postUpdate(apiKey, cmdId, updateMessage):
    url = "https://api.monday.com/v2/"
    headers = {"Authorization": apiKey}
    query = {"query": "mutation{create_update(item_id:" + cmdId + ", body:\"" + updateMessage + "\") {id}}"}
    response = requests.post(url, headers=headers, data=query)
    print(response.json())


def sendCommand(apiKey, boardId, cmd):
    url = "https://api.monday.com/v2/"
    headers = {"Authorization": apiKey}
    query = {"query": "mutation {create_item (board_id: " + boardId + ", group_id: \"topics\", item_name: \"" + cmd + "\") {id}}"}
    response = requests.post(url, headers=headers, data=query)
    print(response.json())


# returns item ID & item (aka command ID & command)
def getCmd(apiKey, boardId):
    url = "https://api.monday.com/v2/"
    headers = {"Authorization": apiKey}
    query = {"query": "{boards(ids:" + boardId + ") {items {name, id}}}"}
    response = requests.post(url, headers=headers, data=query)
    command = response.json()['data']['boards'][0]['items'][-1]['name']
    commandId = response.json()['data']['boards'][0]['items'][-1]['id']
    return command, commandId

# grabs link for most recent file upload for a command
def findFile(apiKey, commandId):
    url = "https://api.monday.com/v2/"
    headers = {"Authorization": apiKey}
    query = {"query": "{items (ids: " + commandId + ") {assets { public_url }}}"}
    response = requests.post(url, headers=headers, data=query)
    # if the items section isn't empty meaning files exist
    if len(response.json()['data']['items']) != 0:
        try:
            return response.json()['data']['items'][-1]['assets'][-1]['public_url']
        # if there's no file associated w/a command, we return nothing
        except IndexError:
            return ""

def main():
    arguments = argparse.ArgumentParser()
    arguments.add_argument("-r", "--respond", help="Respond to a command")
    arguments.add_argument("-bid", "--board-id", help="ID number for board")
    arguments.add_argument("-cid", "--command-id", help="ID number for command")
    arguments.add_argument("-c", "--check-cmd", help="Check for a command")
    arguments.add_argument("-s", "--send-cmd", help="Send a command")
    args = arguments.parse_args()

    if args.respond is None and args.check_cmd is None and args.send_cmd is None:
        print("No arguments! Exiting...")
    else:
        if args.send_cmd is not None:
            # send a command
            if args.board_id is None:
                print("Missing board ID! Must supply board ID via -bid flag in order to send commands!")
            else:
                sendCommand(apiKey, args.board_id, args.send_cmd)
        elif args.check_cmd is not None:
            # check for command
            command, commandId = getCmd(apiKey, args.check_cmd)
            fileUrl = findFile(apiKey, commandId)
            if len(fileUrl) > 0:
                print("Command: {0}\nCommand ID: {1}\nFile Associated With Command: {2}".format(command, commandId, fileUrl))
            else:
                print("Command: {0}\nCommand ID: {1}".format(command, commandId))
        elif args.respond is not None:
            # respond to command
            if args.command_id is None:
                print("Missing command ID! Must supply command ID via -cid flag in order to respond to a command!")
            else:
                postUpdate(apiKey, args.command_id, args.respond)


if __name__ == "__main__":
	main()


