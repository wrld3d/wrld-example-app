import csv

# This takes two files
# 1. meeting room sheet from swallow poi xls exported as csv
# 2. meeting rooms from Bloomberg on-prem feed, as MEETING_ROOM_NAME,spaceid

swallow_meeting_rooms_csv_path = "data/meetingrooms.csv"
feed_meeting_rooms_csv_path = "data/meetingroom-space-ids.csv"
swallow_meeting_room_csv_dest = "data/meetingrooms-output.csv"

feed_meeting_space_ids = {}
assigned_feed_meeting_space_ids = {}
meeting_room_errors = []

with open(feed_meeting_rooms_csv_path, 'rb') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    for row in reader:
        if len(row) > 1 and row[2] in ["GB033", "GB006", "GB025", "GB032", "GB012"]:
            try:
                room_name = row[0]
                if row[2] != "GB033" and '-' in row[0]:
                    room_name = row[0].split("-")[-1]
                feed_meeting_space_ids[room_name.lower()] = int(row[1])
            except:
                pass

#print feed_space_ids.keys()

with open(swallow_meeting_rooms_csv_path, 'rb') as csvfile:
    with open(swallow_meeting_room_csv_dest, 'w') as outputcsv:
        reader = csv.reader(csvfile, delimiter=',')
        meeting_room_errors = []
        for row in reader:
            room_name = row[0].lower()        
            if "castle" in room_name:
                room_name = room_name.replace(" castle", "")
            if room_name in feed_meeting_space_ids:
                row[8] = str(feed_meeting_space_ids[room_name])
                assigned_feed_meeting_space_ids[feed_meeting_space_ids[room_name]] = True
            else:
                meeting_room_errors.append("Cannot find room: {0} ({1},{2})".format(row[0], row[3], row[4]))
            outputcsv.write("{0}\n".format(",".join(row)))

for i in range(10):
    print "\n"

for key in feed_meeting_space_ids.keys():
    feed_space_id = feed_meeting_space_ids[key]
    if not feed_space_id in assigned_feed_meeting_space_ids:
        print "Unassigned: {0} - {1}".format(key, feed_space_id)

for i in range(10):
    print "\n"

print "\n".join(meeting_room_errors)