# source: https://stackoverflow.com/a/6127884
# Hmmmm I think this might delete branches that weren't merged, they're just
# identical, like if you just created a new branch from master...
git branch --merged | egrep -v "(^\*|master|dev)" | xargs git branch -d
