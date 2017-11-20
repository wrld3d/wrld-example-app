import csv

# This takes two files
# 1. meeting room sheet from swallow poi xls exported as csv
# 2. meeting rooms from Bloomberg on-prem feed, as MEETING_ROOM_NAME,spaceid

swallow_desks_csv_path = "data/desks.csv"
feed_desks_csv_path = "data/desk-space-ids.csv"
swallow_desk_csv_dest = "data/desks-output2.csv"

feed_desk_space_ids = {}
assigned_feed_desk_space_ids = {}
desk_errors = []

def fixup_desk_name(desk_name):
    desk_name = desk_name.lower()
    if "pkh3" in desk_name:
        return desk_name.replace("pkh", "pkh-")
    return desk_name

with open(feed_desks_csv_path, 'rb') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    for row in reader:
        if len(row) > 1 and row[2] in ["GB033", "GB006", "GB025", "GB032", "GB012"]:
            desk_name = fixup_desk_name(row[0])
            feed_desk_space_ids[desk_name] = row[1]

print feed_desk_space_ids.keys()

with open(swallow_desks_csv_path, 'rb') as csvfile:
    with open(swallow_desk_csv_dest, 'w') as outputcsv:
        reader = csv.reader(csvfile, delimiter=',')
        for row in reader:
            desk_name = row[0].lower()        
            if desk_name in feed_desk_space_ids:
                row[5] = str(feed_desk_space_ids[desk_name])
                assigned_feed_desk_space_ids[feed_desk_space_ids[desk_name]] = True
            else:
                desk_errors.append("Cannot find desk: {0} ({1},{2})".format(row[0], row[3], row[4]))
            outputcsv.write("{0}\n".format(",".join(row)))

for i in range(10):
    print "\n"

for key in feed_desk_space_ids.keys():
    feed_space_id = feed_desk_space_ids[key]
    if not feed_space_id in assigned_feed_desk_space_ids:
        print "Unassigned: {0} - {1}".format(key, feed_space_id)

for i in range(10):
    print "\n"

print "\n".join(desk_errors)

print "DONE FFS"