import {
  BanknotesIcon,
  UserPlusIcon,
  FireIcon,
  UsersIcon,
  PresentationChartBarIcon,
  ChartBarIcon,
  BellAlertIcon,
  PresentationChartLineIcon,
} from "@heroicons/react/24/solid";

export const statisticsCardsData = [
  {
    color: "gray",
    icon: PresentationChartLineIcon,
    title: "Prediction - Should I water?",
    value: "Watering Required",
    footer: {
      color: "text-red-500",
      value: "-2%",
      label: "than yesterday",
    },
  },
  {
    color: "gray",
    icon:FireIcon,
    title: "Today's Temperature",
    value: "43°C",
    footer: {
      color: "text-green-500",
      value: "+55%",
      label: "than last week",
    },
  },
  {
    color: "gray",
    icon: PresentationChartBarIcon,
    title: "Today's Rainfall Probability",
    value: "72%",
    footer: {
      color: "text-green-500",
      value: "+3%",
      label: "than last month",
    },
  },

  // {
  //   color: "gray",
  //   icon: BellAlertIcon,
  //   title: "Alert",
  //   value: "Water overflow",
  //   footer: {
  //     color: "text-green-500",
  //     value: "+5%",
  //     label: "than yesterday",
  //   },
  // },
];

export default statisticsCardsData;
